package main

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log/slog"
	"net/http"
	"strings"
	"time"

	awsconfig "github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/lambda"
	lambdatypes "github.com/aws/aws-sdk-go-v2/service/lambda/types"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type StresserClient interface {
	Invoke(ctx context.Context, event contracts.StressEvent) (contracts.StressResult, error)
}

type StresserInvokeError struct {
	StatusCode int
	Detail     string
}

func (e *StresserInvokeError) Error() string {
	return e.Detail
}

type LocalDockerStresserClient struct {
	endpoint string
	client   *http.Client
}

func NewLocalDockerStresserClient(endpoint string) *LocalDockerStresserClient {
	return &LocalDockerStresserClient{
		endpoint: endpoint,
		client:   &http.Client{Timeout: 120 * time.Second},
	}
}

func (c *LocalDockerStresserClient) Invoke(ctx context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	slog.Info("stresser_invoke", "mode", "local_docker", "endpoint", c.endpoint)
	body, err := json.Marshal(event)
	if err != nil {
		return contracts.StressResult{}, err
	}
	req, err := http.NewRequestWithContext(ctx, http.MethodPost, c.endpoint, bytes.NewReader(body))
	if err != nil {
		return contracts.StressResult{}, err
	}
	req.Header.Set("Content-Type", "application/json")
	resp, err := c.client.Do(req)
	if err != nil {
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	defer resp.Body.Close()
	if resp.StatusCode < 200 || resp.StatusCode >= 300 {
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	return decodeJSON(resp.Body, "Stresser returned an invalid response, try again shortly.")
}

type LambdaStresserClient struct {
	functionName string
	client       *lambda.Client
}

func NewLambdaStresserClient(ctx context.Context, functionName, region string) (*LambdaStresserClient, error) {
	cfg, err := awsconfig.LoadDefaultConfig(ctx, awsconfig.WithRegion(region))
	if err != nil {
		return nil, err
	}
	return &LambdaStresserClient{
		functionName: functionName,
		client:       lambda.NewFromConfig(cfg),
	}, nil
}

func (c *LambdaStresserClient) Invoke(ctx context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	slog.Info("stresser_invoke", "mode", "lambda", "function", c.functionName)
	payload, err := json.Marshal(event)
	if err != nil {
		return contracts.StressResult{}, err
	}
	resp, err := c.client.Invoke(ctx, &lambda.InvokeInput{
		FunctionName:   &c.functionName,
		InvocationType: lambdatypes.InvocationTypeRequestResponse,
		Payload:        payload,
	})
	if err != nil {
		if strings.Contains(err.Error(), "TooManyRequestsException") {
			return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusTooManyRequests, Detail: "Stresser is at capacity, try again shortly."}
		}
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	if resp.StatusCode >= 500 {
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	if resp.FunctionError != nil && *resp.FunctionError != "" {
		slog.Error("lambda_stresser_function_error", "function", c.functionName, "payload", string(resp.Payload))
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser failed before returning a valid response."}
	}
	return decodeJSON(bytes.NewReader(resp.Payload), "Stresser returned an invalid response, try again shortly.")
}

func MakeStresserClient(ctx context.Context, settings Settings) (StresserClient, error) {
	switch settings.StresserMode {
	case "local_docker":
		return NewLocalDockerStresserClient(settings.StresserLocalEndpoint), nil
	case "lambda":
		if strings.TrimSpace(settings.StresserLambdaFunctionName) == "" {
			return nil, fmt.Errorf("STRESSER_LAMBDA_FUNCTION_NAME must be set for lambda mode")
		}
		return NewLambdaStresserClient(ctx, settings.StresserLambdaFunctionName, settings.AWSRegion)
	default:
		return nil, fmt.Errorf("unknown STRESSER_MODE: %s", settings.StresserMode)
	}
}

func decodeJSON(reader io.Reader, detail string) (contracts.StressResult, error) {
	var payload contracts.StressResult
	if err := json.NewDecoder(reader).Decode(&payload); err != nil {
		return contracts.StressResult{}, &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: detail}
	}
	return payload, nil
}
