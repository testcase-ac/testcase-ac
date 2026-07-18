package stresser

// This file invokes the stresser through the local Docker HTTP endpoint.

import (
	"bytes"
	"context"
	"encoding/json"
	"io"
	"log/slog"
	"net/http"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type DockerClient struct {
	endpoint string
	client   *http.Client
}

func NewDockerClient(endpoint string) *DockerClient {
	return &DockerClient{
		endpoint: endpoint,
		client:   &http.Client{Timeout: 120 * time.Second},
	}
}

func (c *DockerClient) Invoke(ctx context.Context, event contracts.StressEvent, progress ProgressCallback) (contracts.StressResult, error) {
	start := time.Now()
	logger := slog.With("request_id", event.RequestID, "mode", "local_docker", "endpoint", c.endpoint)
	logger.Info("stresser_invoke")

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
		if isRequestContextCanceled(ctx, err) {
			logger.Info("stresser_invoke_canceled", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
			return contracts.StressResult{}, err
		}
		logger.Warn("stresser_invoke_failed", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}
	defer resp.Body.Close()

	if resp.StatusCode < 200 || resp.StatusCode >= 300 {
		logger.Warn("stresser_invoke_failed", "status", resp.StatusCode, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser is unavailable, try again shortly."}
	}

	result, err := decodeDockerResponse(resp.Body, progress)
	if err != nil {
		if progress != nil {
			logger.Warn("stresser_stream_invalid", "err", err)
			err = invalidStresserResponseError()
		}
		logger.Warn("stresser_invoke_failed", "err", err, "elapsed_ms", time.Since(start).Milliseconds())
		return contracts.StressResult{}, err
	}

	logger.Info("stresser_invoke_done", "elapsed_ms", time.Since(start).Milliseconds(), "stresser_error", result.Error)
	return result, nil
}

func decodeDockerResponse(reader io.Reader, progress ProgressCallback) (contracts.StressResult, error) {
	if progress == nil {
		return decodeStressResult(reader)
	}
	decoder := newStressStreamDecoder(progress)
	if _, err := io.Copy(decoder, reader); err != nil {
		return contracts.StressResult{}, err
	}
	return decoder.Finish()
}
