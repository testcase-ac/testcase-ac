package main

// Request flow: main.go -> runtime.go -> handler.go -> stress.go.
// This file adapts AWS Lambda and local HTTP requests to invocation handling.

import (
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"io"
	"log/slog"
	"net/http"
	"strings"
	"sync"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

const ndjsonContentType = "application/x-ndjson"

type responseReader struct {
	reader      io.ReadCloser
	contentType string
}

func (r *responseReader) Read(payload []byte) (int, error) { return r.reader.Read(payload) }
func (r *responseReader) Close() error                     { return r.reader.Close() }

func (r *responseReader) ContentType() string {
	return r.contentType
}

// common handler for both prod and local.
// in prod, aws-lambda-go decodes the raw request body into StressEvent and pass it to this handler.
// in local, `localHandler` does the job instead.
func lambdaHandler(event contracts.StressEvent) (*responseReader, error) {
	if event.StreamProgress {
		return streamInvocation(event), nil
	}
	result, err := handleInvocation(event, nil)
	if err != nil {
		return nil, err
	}
	payload, err := json.Marshal(result)
	if err != nil {
		return nil, err
	}
	return &responseReader{reader: io.NopCloser(bytes.NewReader(payload)), contentType: "application/json"}, nil
}

func streamInvocation(event contracts.StressEvent) *responseReader {
	reader, writer := io.Pipe()
	go func() {
		encoder := json.NewEncoder(writer)
		var writeErr error
		result, err := handleInvocation(event, func(progress contracts.StressProgress) {
			if writeErr == nil {
				writeErr = encoder.Encode(contracts.StressStreamRecord{Type: "progress", Progress: &progress})
			}
		})
		if err == nil && writeErr == nil {
			writeErr = encoder.Encode(contracts.StressStreamRecord{Type: "result", Result: &result})
		}
		if err != nil {
			_ = writer.CloseWithError(err)
			return
		}
		if writeErr != nil {
			_ = writer.CloseWithError(writeErr)
			return
		}
		_ = writer.Close()
	}()
	return &responseReader{reader: reader, contentType: ndjsonContentType}
}

type streamingTransport struct {
	base http.RoundTripper
}

func (t streamingTransport) RoundTrip(request *http.Request) (*http.Response, error) {
	if request.Method != http.MethodPost || request.Header.Get("Content-Type") != ndjsonContentType || !strings.Contains(request.URL.Path, "/runtime/invocation/") || !strings.HasSuffix(request.URL.Path, "/response") {
		return t.base.RoundTrip(request)
	}

	streamRequest := request.Clone(request.Context())
	streamRequest.Trailer = request.Trailer
	streamRequest.Header.Set("Lambda-Runtime-Function-Response-Mode", "streaming")
	streamRequest.ContentLength = -1
	streamRequest.TransferEncoding = []string{"chunked"}
	streamRequest.Close = true
	return t.base.RoundTrip(streamRequest)
}

func installStreamingTransport() {
	http.DefaultTransport = streamingTransport{base: http.DefaultTransport}
}

type flushWriter struct {
	w http.ResponseWriter
}

func (w flushWriter) Write(payload []byte) (int, error) {
	n, err := w.w.Write(payload)
	if err == nil {
		err = http.NewResponseController(w.w).Flush()
	}
	return n, err
}

func localHandler() http.Handler {
	mux := http.NewServeMux()
	var invocationMu sync.Mutex
	mux.HandleFunc("POST /stress", func(w http.ResponseWriter, request *http.Request) {
		var event contracts.StressEvent
		decoder := json.NewDecoder(http.MaxBytesReader(w, request.Body, 6<<20))
		if err := decoder.Decode(&event); err != nil {
			http.Error(w, "Invalid request", http.StatusBadRequest)
			return
		}
		if err := decoder.Decode(&struct{}{}); err != io.EOF {
			http.Error(w, "Invalid request", http.StatusBadRequest)
			return
		}

		// simulate the behavior of AWS Lambda runtime, which processes one invocation at a time.
		invocationMu.Lock()
		defer invocationMu.Unlock()
		response, err := lambdaHandler(event)
		if err != nil {
			http.Error(w, "Internal server error", http.StatusInternalServerError)
			return
		}
		defer response.Close()
		w.Header().Set("Content-Type", response.ContentType())
		w.WriteHeader(http.StatusOK)
		var target io.Writer = w
		if event.StreamProgress {
			target = flushWriter{w: w}
		}
		if _, err := io.Copy(target, response); err != nil && !errors.Is(err, context.Canceled) {
			slog.Warn("local_stresser_response_failed", "request_id", event.RequestID, "err", err)
		}
	})
	return mux
}
