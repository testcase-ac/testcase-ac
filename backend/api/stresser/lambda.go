package stresser

// This file invokes the stresser through buffered or streaming AWS Lambda calls.

import (
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"net/http"
	"time"

	"github.com/aws/aws-sdk-go-v2/aws"
	awsconfig "github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/lambda"
	lambdatypes "github.com/aws/aws-sdk-go-v2/service/lambda/types"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type LambdaClient struct {
	functionName string
	client       *lambda.Client
}

func NewLambdaClient(ctx context.Context, functionName, region string) (*LambdaClient, error) {
	cfg, err := awsconfig.LoadDefaultConfig(ctx, awsconfig.WithRegion(region))
	if err != nil {
		return nil, err
	}
	return &LambdaClient{
		functionName: functionName,
		client:       lambda.NewFromConfig(cfg),
	}, nil
}

func (c *LambdaClient) Invoke(ctx context.Context, event contracts.StressEvent, progress ProgressCallback) (contracts.StressResult, error) {
	start := time.Now()
	logger := slog.With("request_id", event.RequestID, "mode", "lambda", "function", c.functionName)
	logger.Info("stresser_invoke")

	payload, err := json.Marshal(event)
	if err != nil {
		return contracts.StressResult{}, err
	}

	var result contracts.StressResult
	if progress == nil {
		result, err = c.invokeBuffered(ctx, payload, logger, start)
	} else {
		result, err = c.invokeStreamed(ctx, payload, progress, logger, start)
	}
	if err != nil {
		return contracts.StressResult{}, err
	}

	logger.Info("stresser_invoke_done", "elapsed_ms", time.Since(start).Milliseconds(), "stresser_error", result.Error)
	return result, nil
}

func (c *LambdaClient) invokeBuffered(ctx context.Context, payload []byte, logger *slog.Logger, start time.Time) (contracts.StressResult, error) {
	resp, err := c.client.Invoke(ctx, &lambda.InvokeInput{
		FunctionName:   &c.functionName,
		InvocationType: lambdatypes.InvocationTypeRequestResponse,
		Payload:        payload,
	})
	if err != nil {
		return contracts.StressResult{}, lambdaInvocationError(ctx, err, logger, start)
	}
	if resp.StatusCode >= 500 {
		logger.Warn("stresser_invoke_failed", "status", resp.StatusCode, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	if resp.FunctionError != nil && *resp.FunctionError != "" {
		logger.Error("lambda_stresser_function_error", "payload", string(resp.Payload), "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser failed before returning a valid response."}
	}

	result, err := decodeStressResult(bytes.NewReader(resp.Payload))
	if err != nil {
		logger.Warn("stresser_invoke_failed", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, err
	}
	return result, nil
}

func (c *LambdaClient) invokeStreamed(ctx context.Context, payload []byte, progress ProgressCallback, logger *slog.Logger, start time.Time) (contracts.StressResult, error) {
	resp, err := c.client.InvokeWithResponseStream(ctx, &lambda.InvokeWithResponseStreamInput{
		FunctionName:   &c.functionName,
		InvocationType: lambdatypes.ResponseStreamingInvocationTypeRequestResponse,
		Payload:        payload,
	})
	if err != nil {
		return contracts.StressResult{}, lambdaInvocationError(ctx, err, logger, start)
	}
	if resp.StatusCode >= 500 || resp.GetStream() == nil {
		logger.Warn("stresser_invoke_failed", "status", resp.StatusCode, "stream_missing", resp.GetStream() == nil, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}

	stream := resp.GetStream()
	result, decodeErr := decodeLambdaResponseStream(stream, progress)
	closeErr := stream.Close()
	if decodeErr != nil || closeErr != nil {
		logger.Warn("stresser_invoke_failed", "err", errors.Join(decodeErr, closeErr), "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, invalidStresserResponseError()
	}
	return result, nil
}

func lambdaInvocationError(ctx context.Context, err error, logger *slog.Logger, start time.Time) error {
	if isRequestContextCanceled(ctx, err) {
		logger.Info("stresser_invoke_canceled", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
		return err
	}
	var capacityError *lambdatypes.TooManyRequestsException
	if errors.As(err, &capacityError) {
		logger.Warn("stresser_invoke_failed", "err", err, "status", http.StatusTooManyRequests, "elapsed_ms", time.Since(start).Milliseconds())
		return &InvokeError{StatusCode: http.StatusTooManyRequests, Detail: "Stresser is at capacity, try again shortly."}
	}
	logger.Warn("stresser_invoke_failed", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
	return &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
}

func decodeLambdaResponseStream(stream *lambda.InvokeWithResponseStreamEventStream, progress ProgressCallback) (contracts.StressResult, error) {
	decoder := newStressStreamDecoder(progress)
	complete := false
	for event := range stream.Events() {
		switch event := event.(type) {
		case *lambdatypes.InvokeWithResponseStreamResponseEventMemberPayloadChunk:
			if complete {
				return contracts.StressResult{}, fmt.Errorf("payload received after completion")
			}
			if _, err := decoder.Write(event.Value.Payload); err != nil {
				return contracts.StressResult{}, err
			}
		case *lambdatypes.InvokeWithResponseStreamResponseEventMemberInvokeComplete:
			if complete {
				return contracts.StressResult{}, fmt.Errorf("duplicate completion event")
			}
			complete = true
			if event.Value.ErrorCode != nil && *event.Value.ErrorCode != "" {
				return contracts.StressResult{}, fmt.Errorf("lambda stream failed: %s: %s", *event.Value.ErrorCode, aws.ToString(event.Value.ErrorDetails))
			}
		default:
			return contracts.StressResult{}, fmt.Errorf("unknown lambda stream event %T", event)
		}
	}
	if err := stream.Err(); err != nil {
		return contracts.StressResult{}, err
	}
	if !complete {
		return contracts.StressResult{}, fmt.Errorf("lambda stream ended without completion")
	}
	return decoder.Finish()
}
