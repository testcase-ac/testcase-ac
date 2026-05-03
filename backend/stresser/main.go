package main

import (
	"context"
	"log/slog"
	"os"
	"runtime/debug"
	"time"

	"github.com/aws/aws-lambda-go/lambda"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

var (
	runOperationStress  = operationStress
	runCheckAndCleanTmp = checkAndCleanTmp
	runLogTmpUsage      = logTmpUsage
)

func handler(_ context.Context, event contracts.StressEvent) (result contracts.StressResult, err error) {
	requestID := event.RequestID
	startTime := time.Now()
	if event.Operation == "" {
		event.Operation = contracts.OperationStress
	}
	slog.Info("stresser_invocation_start", "request_id", requestID, "operation", event.Operation)
	defer func() {
		if recovered := recover(); recovered != nil {
			slog.Error(
				"stresser_internal_panic",
				"request_id", requestID,
				"panic", recovered,
				"stack", string(debug.Stack()),
			)
			result = NewResponseError(
				contracts.ErrorTypeInternalServerError,
				map[string]any{"message": "Internal server error"},
			).ToResponse(requestID)
			result.RuntimeSeconds = util.RoundSeconds(time.Since(startTime))
			err = nil
		}
	}()
	defer runLogTmpUsage()

	if err := runCheckAndCleanTmp(); err != nil {
		slog.Warn("tmp_cleanup_failed", "request_id", requestID, "err", err)
	}

	switch event.Operation {
	case contracts.OperationStress:
		result, err = runOperationStress(event)
	default:
		err = NewResponseError(
			contracts.ErrorTypeInvalidOperation,
			map[string]any{"message": "Invalid operation: " + string(event.Operation)},
		)
	}
	if err != nil {
		if responseErr, ok := err.(*ResponseError); ok {
			slog.Warn("stresser_response_error", "request_id", requestID, "error_type", responseErr.errorType)
			response := responseErr.ToResponse(requestID)
			response.RuntimeSeconds = util.RoundSeconds(time.Since(startTime))
			return response, nil
		}
		slog.Error(
			"stresser_internal_error",
			"request_id", requestID,
			"err", err,
			"stack", string(debug.Stack()),
		)
		response := NewResponseError(
			contracts.ErrorTypeInternalServerError,
			map[string]any{"message": "Internal server error"},
		).ToResponse(requestID)
		response.RuntimeSeconds = util.RoundSeconds(time.Since(startTime))
		return response, nil
	}

	result.RequestID = requestID
	result.RuntimeSeconds = util.RoundSeconds(time.Since(startTime))
	slog.Info(
		"stresser_invocation_done",
		"request_id", requestID,
		"runtime_seconds", result.RuntimeSeconds,
		"error", result.Error,
		"total_cases", result.TotalCases,
		"wrong_cases", result.WrongCasesCount,
		"execution_failed_cases", result.ExecutionFailedCasesCount,
	)
	return result, nil
}

func main() {
	slog.SetDefault(slog.New(slog.NewJSONHandler(os.Stdout, nil)))
	lambda.Start(handler)
}
