package main

import (
	"context"
	"errors"
	"strings"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestHandlerPanicReturnsInternalErrorResponse(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(contracts.StressEvent) (contracts.StressResult, error) {
		panic("test panic")
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	result, err := handler(context.Background(), contracts.StressEvent{
		Operation: contracts.OperationStress,
		RequestID: "panic-request",
	})
	if err != nil {
		t.Fatalf("handler() error = %v", err)
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

func TestHandlerInternalErrorReturnsGenericResponse(t *testing.T) {
	previousRunOperationStress := runOperationStress
	previousRunCheckAndCleanTmp := runCheckAndCleanTmp
	previousRunLogTmpUsage := runLogTmpUsage
	runOperationStress = func(contracts.StressEvent) (contracts.StressResult, error) {
		return contracts.StressResult{}, errors.New("secret internal detail")
	}
	runCheckAndCleanTmp = func() error { return nil }
	runLogTmpUsage = func() {}
	t.Cleanup(func() {
		runOperationStress = previousRunOperationStress
		runCheckAndCleanTmp = previousRunCheckAndCleanTmp
		runLogTmpUsage = previousRunLogTmpUsage
	})

	result, err := handler(context.Background(), contracts.StressEvent{
		Operation: contracts.OperationStress,
		RequestID: "internal-error-request",
	})
	if err != nil {
		t.Fatalf("handler() error = %v", err)
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
