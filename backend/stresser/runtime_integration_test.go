package main

// Exercise the actual SDK startup path against a fake Lambda Runtime API.

import (
	"bytes"
	"context"
	"encoding/json"
	"io"
	"net/http"
	"net/http/httptest"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"sync/atomic"
	"testing"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestLambdaRuntimeAPIStartup(t *testing.T) {
	if os.Getenv("TEST_LAMBDA_RUNTIME_CHILD") == "1" {
		runCheckAndCleanTmp = func() error { return nil }
		runLogTmpUsage = func() {}
		runOperationStress = func(event contracts.StressEvent, progress func(contracts.StressProgress)) (contracts.StressResult, error) {
			if event.StreamProgress {
				progress(contracts.StressProgress{Stage: contracts.StressProgressStageRunning})
				// The fake Runtime API releases this call only after reading progress.
				response, err := http.Get(os.Getenv("TEST_LAMBDA_RELEASE_URL"))
				if err != nil {
					return contracts.StressResult{}, err
				}
				_ = response.Body.Close()
			}
			return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
		}
		main()
		return
	}

	for _, streamed := range []bool{false, true} {
		name := "buffered"
		if streamed {
			name = "streamed"
		}
		t.Run(name, func(t *testing.T) {
			// Given: a Runtime API that serves one invocation and reads its response.
			ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
			defer cancel()
			type invocationResponse struct {
				mode        string
				contentType string
				body        []byte
				err         error
			}
			posted := make(chan invocationResponse, 1)
			progressRead := make(chan struct{})
			var invocationSent atomic.Bool
			server := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
				switch {
				case r.URL.Path == "/release":
					select {
					case <-progressRead:
						w.WriteHeader(http.StatusOK)
					case <-r.Context().Done():
					}
				case r.Method == http.MethodGet && strings.HasSuffix(r.URL.Path, "/next"):
					if invocationSent.Swap(true) {
						<-r.Context().Done()
						return
					}
					w.Header().Set("Lambda-Runtime-Aws-Request-Id", "startup-test")
					w.Header().Set("Lambda-Runtime-Deadline-Ms", strconv.FormatInt(time.Now().Add(time.Minute).UnixMilli(), 10))
					_ = json.NewEncoder(w).Encode(contracts.StressEvent{Operation: contracts.OperationStress, StreamProgress: streamed})
				case r.Method == http.MethodPost && strings.HasSuffix(r.URL.Path, "/startup-test/response"):
					result := invocationResponse{mode: r.Header.Get("Lambda-Runtime-Function-Response-Mode"), contentType: r.Header.Get("Content-Type")}
					if streamed {
						decoder := json.NewDecoder(r.Body)
						var first contracts.StressStreamRecord
						result.err = decoder.Decode(&first)
						if result.err == nil && first.Type == "progress" {
							close(progressRead)
							var last contracts.StressStreamRecord
							result.err = decoder.Decode(&last)
							if result.err == nil && last.Type == "result" {
								result.body, result.err = json.Marshal(last.Result)
								if result.err == nil {
									_, result.err = io.Copy(io.Discard, r.Body)
								}
							}
						}
					} else {
						result.body, result.err = io.ReadAll(r.Body)
					}
					posted <- result
					w.WriteHeader(http.StatusAccepted)
				default:
					w.WriteHeader(http.StatusNotFound)
				}
			}))
			defer server.Close()

			// When: the production entrypoint starts the installed Lambda SDK.
			command := exec.CommandContext(ctx, os.Args[0], "-test.run=^TestLambdaRuntimeAPIStartup$")
			command.Env = append(os.Environ(), "TEST_LAMBDA_RUNTIME_CHILD=1", "AWS_LAMBDA_RUNTIME_API="+strings.TrimPrefix(server.URL, "http://"), "TEST_LAMBDA_RELEASE_URL="+server.URL+"/release")
			var output bytes.Buffer
			command.Stdout = &output
			command.Stderr = &output
			if err := command.Start(); err != nil {
				t.Fatal(err)
			}
			done := make(chan error, 1)
			go func() { done <- command.Wait() }()
			defer func() {
				cancel()
				<-done
			}()

			// Then: the Runtime API receives a valid buffered or incremental response.
			var result invocationResponse
			select {
			case result = <-posted:
			case err := <-done:
				done <- err
				t.Fatalf("Lambda startup exited: %v\n%s", err, output.String())
			case <-ctx.Done():
				t.Fatal("Lambda did not complete the Runtime API invocation")
			}
			if result.err != nil {
				t.Fatal(result.err)
			}
			if streamed && (result.mode != "streaming" || result.contentType != ndjsonContentType) {
				t.Fatalf("streamed response mode=%q content-type=%q", result.mode, result.contentType)
			}
			if !streamed && (result.mode != "" || result.contentType != "application/json") {
				t.Fatalf("buffered response mode=%q content-type=%q", result.mode, result.contentType)
			}
			var response contracts.StressResult
			if err := json.Unmarshal(result.body, &response); err != nil {
				t.Fatalf("decode invocation response: %v; body=%q", err, result.body)
			}
			if response.TotalCases != 1 || response.CorrectCasesCount != 1 || response.Error {
				t.Fatalf("invocation response = %+v", response)
			}
		})
	}
}
