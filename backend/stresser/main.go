package main

import (
	"context"
	"log"
	"runtime/debug"
	"time"

	"github.com/aws/aws-lambda-go/lambda"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

var (
	runOperationStress  = operationStress
	runCheckAndCleanTmp = checkAndCleanTmp
	runLogTmpUsage      = logTmpUsage
)

func handler(_ context.Context, event contracts.StressEvent) (result contracts.StressResult, err error) {
	requestID := event.RequestID
	startTime := time.Now()
	log.Printf("stresser invocation start requestId=%s operation=%s", requestID, event.Operation)
	defer func() {
		if recovered := recover(); recovered != nil {
			log.Printf("stresser internal panic requestId=%s panic=%v stack=%s", requestID, recovered, string(debug.Stack()))
			result = NewResponseError(
				contracts.ErrorTypeInternalServerError,
				map[string]any{"message": "Internal server error"},
			).ToResponse(requestID)
			result.RuntimeSeconds = roundSeconds(time.Since(startTime))
			err = nil
		}
	}()
	defer runLogTmpUsage()

	if err := runCheckAndCleanTmp(); err != nil {
		log.Printf("tmp cleanup failed requestId=%s err=%v", requestID, err)
	}

	if event.Operation == "" {
		event.Operation = contracts.OperationStress
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
			log.Printf("stresser ResponseError requestId=%s type=%s", requestID, responseErr.errorType)
			response := responseErr.ToResponse(requestID)
			response.RuntimeSeconds = roundSeconds(time.Since(startTime))
			return response, nil
		}
		log.Printf("stresser internal error requestId=%s err=%v stack=%s", requestID, err, string(debug.Stack()))
		response := NewResponseError(
			contracts.ErrorTypeInternalServerError,
			map[string]any{"message": "Internal server error"},
		).ToResponse(requestID)
		response.RuntimeSeconds = roundSeconds(time.Since(startTime))
		return response, nil
	}

	result.RequestID = requestID
	result.RuntimeSeconds = roundSeconds(time.Since(startTime))
	log.Printf("stresser invocation done requestId=%s", requestID)
	return result, nil
}

func main() {
	log.SetFlags(log.LstdFlags)
	lambda.Start(handler)
}
