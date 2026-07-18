// Package stresser invokes the isolated stress runtime for the API through
// Docker or Lambda and decodes its buffered or streamed responses.
package stresser

import (
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"net/http"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type Client interface {
	Invoke(ctx context.Context, event contracts.StressEvent, progress ProgressCallback) (contracts.StressResult, error)
}

type ProgressCallback func(contracts.StressProgress) error

func isRequestContextCanceled(ctx context.Context, err error) bool {
	return errors.Is(err, context.Canceled) || errors.Is(ctx.Err(), context.Canceled)
}

type InvokeError struct {
	StatusCode int
	Detail     string
}

func (e *InvokeError) Error() string {
	return e.Detail
}

func decodeStressResult(reader io.Reader) (contracts.StressResult, error) {
	var result contracts.StressResult
	if err := json.NewDecoder(reader).Decode(&result); err != nil {
		return contracts.StressResult{}, invalidStresserResponseError()
	}
	return result, nil
}

type stressStreamDecoder struct {
	pending  []byte
	progress ProgressCallback
	result   *contracts.StressResult
}

func newStressStreamDecoder(progress ProgressCallback) *stressStreamDecoder {
	return &stressStreamDecoder{progress: progress}
}

func (d *stressStreamDecoder) Write(chunk []byte) (int, error) {
	d.pending = append(d.pending, chunk...)
	for {
		line, rest, ok := bytes.Cut(d.pending, []byte{'\n'})
		if !ok {
			return len(chunk), nil
		}
		d.pending = rest
		if len(bytes.TrimSpace(line)) == 0 {
			continue
		}
		if err := d.decodeRecord(line); err != nil {
			return len(chunk), err
		}
	}
}

func (d *stressStreamDecoder) Finish() (contracts.StressResult, error) {
	if len(bytes.TrimSpace(d.pending)) > 0 {
		if err := d.decodeRecord(d.pending); err != nil {
			return contracts.StressResult{}, err
		}
	}
	if d.result == nil {
		return contracts.StressResult{}, fmt.Errorf("stream ended without a final result")
	}
	return *d.result, nil
}

func (d *stressStreamDecoder) decodeRecord(line []byte) error {
	if d.result != nil {
		return fmt.Errorf("stream contains data after the final result")
	}
	var record contracts.StressStreamRecord
	if err := json.Unmarshal(line, &record); err != nil {
		return err
	}
	switch record.Type {
	case "progress":
		if record.Progress == nil || record.Result != nil {
			return fmt.Errorf("invalid progress record")
		}
		if d.progress != nil {
			return d.progress(*record.Progress)
		}
		return nil
	case "result":
		if record.Result == nil || record.Progress != nil {
			return fmt.Errorf("invalid result record")
		}
		d.result = record.Result
		return nil
	default:
		return fmt.Errorf("unknown stream record type %q", record.Type)
	}
}

func invalidStresserResponseError() error {
	return &InvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "Stresser returned an invalid response, try again shortly."}
}
