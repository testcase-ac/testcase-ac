package main

import (
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"io"
	"log/slog"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
	"time"

	"github.com/aws/aws-lambda-go/lambda"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type roundTripFunc func(*http.Request) (*http.Response, error)

func (f roundTripFunc) RoundTrip(request *http.Request) (*http.Response, error) {
	return f(request)
}

func TestProgressReporterLogsAndForwards(t *testing.T) {
	previousLogger := slog.Default()
	var output bytes.Buffer
	slog.SetDefault(slog.New(slog.NewJSONHandler(&output, nil)))
	t.Cleanup(func() { slog.SetDefault(previousLogger) })

	completed := 7
	want := contracts.StressProgress{Stage: contracts.StressProgressStageRunning, CompletedIterations: &completed}
	var forwarded contracts.StressProgress
	newProgressReporter("progress-request", func(progress contracts.StressProgress) {
		forwarded = progress
	})(want)

	if forwarded.CompletedIterations == nil || *forwarded.CompletedIterations != completed {
		t.Fatalf("forwarded progress = %#v, want completed iteration %d", forwarded, completed)
	}
	var entry struct {
		Message   string                   `json:"msg"`
		RequestID string                   `json:"request_id"`
		Progress  contracts.StressProgress `json:"progress"`
	}
	if err := json.NewDecoder(&output).Decode(&entry); err != nil {
		t.Fatalf("Decode(log) error = %v; output = %q", err, output.String())
	}
	if entry.Message != "stress_progress" || entry.RequestID != "progress-request" || entry.Progress.CompletedIterations == nil || *entry.Progress.CompletedIterations != completed {
		t.Fatalf("log entry = %#v, want progress request at iteration %d", entry, completed)
	}
}

func TestHandleInvocationPanicReturnsInternalErrorResponse(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(contracts.StressEvent, func(contracts.StressProgress)) (contracts.StressResult, error) {
		panic("test panic")
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	result, err := handleInvocation(contracts.StressEvent{
		Operation: contracts.OperationStress,
		RequestID: "panic-request",
	}, nil)
	if err != nil {
		t.Fatalf("handleInvocation() error = %v", err)
	}
	if !result.Error {
		t.Fatalf("result.Error = false, want true; result = %+v", result)
	}
	if result.ErrorType != contracts.ErrorTypeInternalServerError {
		t.Fatalf("ErrorType = %q, want %q", result.ErrorType, contracts.ErrorTypeInternalServerError)
	}
	if result.RequestID != "panic-request" {
		t.Fatalf("RequestID = %q, want panic-request", result.RequestID)
	}
	if !strings.Contains(result.Message, "Internal server error") {
		t.Fatalf("Message = %q, want generic internal error detail", result.Message)
	}
	if strings.Contains(result.Message, "test panic") {
		t.Fatalf("Message = %q, should not expose panic detail", result.Message)
	}
}

func TestHandleInvocationInternalErrorReturnsGenericResponse(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(contracts.StressEvent, func(contracts.StressProgress)) (contracts.StressResult, error) {
		return contracts.StressResult{}, errors.New("secret internal detail")
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	result, err := handleInvocation(contracts.StressEvent{
		Operation: contracts.OperationStress,
		RequestID: "internal-error-request",
	}, nil)
	if err != nil {
		t.Fatalf("handleInvocation() error = %v", err)
	}
	if !result.Error {
		t.Fatalf("result.Error = false, want true; result = %+v", result)
	}
	if result.ErrorType != contracts.ErrorTypeInternalServerError {
		t.Fatalf("ErrorType = %q, want %q", result.ErrorType, contracts.ErrorTypeInternalServerError)
	}
	if result.RequestID != "internal-error-request" {
		t.Fatalf("RequestID = %q, want internal-error-request", result.RequestID)
	}
	if !strings.Contains(result.Message, "Internal server error") {
		t.Fatalf("Message = %q, want generic internal error detail", result.Message)
	}
	if strings.Contains(result.Message, "secret internal detail") || strings.Contains(result.Message, "goroutine") {
		t.Fatalf("Message = %q, should not expose internal error detail or stack", result.Message)
	}
}

func TestLambdaHandlerStreamsProgressAndFinalResult(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(_ contracts.StressEvent, progress func(contracts.StressProgress)) (contracts.StressResult, error) {
		progress(contracts.StressProgress{Stage: contracts.StressProgressStageCompiling, Source: contracts.StressProgressSourceTarget})
		return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	reader, err := lambdaHandler(contracts.StressEvent{
		Operation:      contracts.OperationStress,
		RequestID:      "stream-request",
		StreamProgress: true,
	})
	if err != nil {
		t.Fatalf("lambdaHandler() error = %v", err)
	}
	defer reader.Close()
	if got := reader.ContentType(); got != "application/x-ndjson" {
		t.Fatalf("ContentType() = %q, want application/x-ndjson", got)
	}

	decoder := json.NewDecoder(reader)
	var progressRecord contracts.StressStreamRecord
	if err := decoder.Decode(&progressRecord); err != nil {
		t.Fatalf("Decode(progress) error = %v", err)
	}
	if progressRecord.Type != "progress" || progressRecord.Progress == nil || progressRecord.Progress.Source != contracts.StressProgressSourceTarget {
		t.Fatalf("progress record = %#v", progressRecord)
	}
	var resultRecord contracts.StressStreamRecord
	if err := decoder.Decode(&resultRecord); err != nil {
		t.Fatalf("Decode(result) error = %v", err)
	}
	if resultRecord.Type != "result" || resultRecord.Result == nil || resultRecord.Result.RequestID != "stream-request" {
		t.Fatalf("result record = %#v", resultRecord)
	}
	if err := decoder.Decode(&contracts.StressStreamRecord{}); err != io.EOF {
		t.Fatalf("third Decode() error = %v, want EOF", err)
	}
}

func TestAWSLambdaHandlerPassesThroughStreamReader(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(_ contracts.StressEvent, progress func(contracts.StressProgress)) (contracts.StressResult, error) {
		progress(contracts.StressProgress{Stage: contracts.StressProgressStageFinalizing})
		return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})
	event, err := json.Marshal(contracts.StressEvent{
		Operation:      contracts.OperationStress,
		RequestID:      "aws-stream-request",
		StreamProgress: true,
	})
	if err != nil {
		t.Fatal(err)
	}

	payload, err := lambda.NewHandler(lambdaHandler).Invoke(context.Background(), event)
	if err != nil {
		t.Fatalf("Invoke() error = %v", err)
	}
	decoder := json.NewDecoder(bytes.NewReader(payload))
	var progress contracts.StressStreamRecord
	if err := decoder.Decode(&progress); err != nil {
		t.Fatalf("Decode(progress) error = %v; payload = %s", err, payload)
	}
	if progress.Type != "progress" || progress.Progress == nil {
		t.Fatalf("progress = %#v; payload = %s", progress, payload)
	}
	var result contracts.StressStreamRecord
	if err := decoder.Decode(&result); err != nil {
		t.Fatalf("Decode(result) error = %v; payload = %s", err, payload)
	}
	if result.Type != "result" || result.Result == nil {
		t.Fatalf("result = %#v; payload = %s", result, payload)
	}
}

func TestLambdaHandlerKeepsBufferedJSONResponse(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(contracts.StressEvent, func(contracts.StressProgress)) (contracts.StressResult, error) {
		return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	reader, err := lambdaHandler(contracts.StressEvent{
		Operation: contracts.OperationStress,
		RequestID: "buffered-request",
	})
	if err != nil {
		t.Fatalf("lambdaHandler() error = %v", err)
	}
	defer reader.Close()
	if got := reader.ContentType(); got != "application/json" {
		t.Fatalf("ContentType() = %q, want application/json", got)
	}
	var result contracts.StressResult
	if err := json.NewDecoder(reader).Decode(&result); err != nil {
		t.Fatalf("Decode() error = %v", err)
	}
	if result.RequestID != "buffered-request" || result.CorrectCasesCount != 1 {
		t.Fatalf("result = %+v", result)
	}
}

func TestLocalHandlerRunsOneInvocationAtATime(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	started := make(chan struct{})
	release := make(chan struct{})
	runOperationStress = func(_ contracts.StressEvent, progress func(contracts.StressProgress)) (contracts.StressResult, error) {
		started <- struct{}{}
		<-release
		progress(contracts.StressProgress{Stage: contracts.StressProgressStageFinalizing})
		return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	server := httptest.NewServer(localHandler())
	defer server.Close()
	payload := []byte(`{"operation":"stress","streamProgress":true}`)
	done := make(chan error, 2)
	invoke := func() {
		response, err := http.Post(server.URL+"/stress", "application/json", bytes.NewReader(payload))
		if err == nil {
			_, err = io.ReadAll(response.Body)
			closeErr := response.Body.Close()
			if err == nil {
				err = closeErr
			}
		}
		done <- err
	}

	go invoke()
	<-started
	go invoke()
	concurrent := false
	select {
	case <-started:
		concurrent = true
		release <- struct{}{}
		release <- struct{}{}
	case <-time.After(100 * time.Millisecond):
		release <- struct{}{}
		<-started
		release <- struct{}{}
	}
	for range 2 {
		if err := <-done; err != nil {
			t.Fatalf("local invocation error = %v", err)
		}
	}
	if concurrent {
		t.Fatal("second local invocation started before the first finished")
	}
}

func TestStreamingTransportOnlyMarksNDJSONResponses(t *testing.T) {
	requests := make(chan *http.Request, 2)
	transport := streamingTransport{base: roundTripFunc(func(request *http.Request) (*http.Response, error) {
		requests <- request
		return &http.Response{StatusCode: http.StatusAccepted, Body: io.NopCloser(bytes.NewReader(nil))}, nil
	})}

	streamRequest, err := http.NewRequest(http.MethodPost, "http://runtime/2018-06-01/runtime/invocation/request-id/response", strings.NewReader("progress"))
	if err != nil {
		t.Fatal(err)
	}
	streamRequest.Header.Set("Content-Type", "application/x-ndjson")
	streamRequest.Trailer = http.Header{"Lambda-Runtime-Function-Error-Type": []string{"late-error"}}
	if _, err := transport.RoundTrip(streamRequest); err != nil {
		t.Fatalf("RoundTrip(stream) error = %v", err)
	}
	streamRequest.Trailer.Set("Lambda-Runtime-Function-Error-Type", "later-error")
	gotStream := <-requests
	if got := gotStream.Header.Get("Lambda-Runtime-Function-Response-Mode"); got != "streaming" {
		t.Fatalf("response mode = %q, want streaming", got)
	}
	if len(gotStream.TransferEncoding) != 1 || gotStream.TransferEncoding[0] != "chunked" {
		t.Fatalf("TransferEncoding = %v, want [chunked]", gotStream.TransferEncoding)
	}
	if !gotStream.Close {
		t.Fatal("Close = false, want true")
	}
	if gotStream.Trailer.Get("Lambda-Runtime-Function-Error-Type") != "later-error" {
		t.Fatalf("Trailer = %v, want preserved late error", gotStream.Trailer)
	}

	jsonRequest, err := http.NewRequest(http.MethodPost, "http://runtime/2018-06-01/runtime/invocation/request-id/response", strings.NewReader("{}"))
	if err != nil {
		t.Fatal(err)
	}
	jsonRequest.Header.Set("Content-Type", "application/json")
	if _, err := transport.RoundTrip(jsonRequest); err != nil {
		t.Fatalf("RoundTrip(json) error = %v", err)
	}
	gotJSON := <-requests
	if got := gotJSON.Header.Get("Lambda-Runtime-Function-Response-Mode"); got != "" || len(gotJSON.TransferEncoding) != 0 || gotJSON.Close {
		t.Fatalf("normal request was modified: header=%q transfer=%v close=%v", got, gotJSON.TransferEncoding, gotJSON.Close)
	}
}
