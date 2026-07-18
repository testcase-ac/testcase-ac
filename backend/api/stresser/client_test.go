package stresser

import (
	"encoding/json"
	"reflect"
	"testing"

	"github.com/aws/aws-sdk-go-v2/service/lambda"
	lambdatypes "github.com/aws/aws-sdk-go-v2/service/lambda/types"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type fakeLambdaStreamReader struct {
	events chan lambdatypes.InvokeWithResponseStreamResponseEvent
	err    error
}

func (r *fakeLambdaStreamReader) Events() <-chan lambdatypes.InvokeWithResponseStreamResponseEvent {
	return r.events
}

func (r *fakeLambdaStreamReader) Close() error { return nil }
func (r *fakeLambdaStreamReader) Err() error   { return r.err }

func TestStressStreamDecoderHandlesArbitraryChunks(t *testing.T) {
	completed := 1
	records := []contracts.StressStreamRecord{
		{Type: "progress", Progress: &contracts.StressProgress{Stage: contracts.StressProgressStageCompiling, Source: contracts.StressProgressSourceSinglegen, SourceID: "한글.cpp"}},
		{Type: "progress", Progress: &contracts.StressProgress{Stage: contracts.StressProgressStageRunning, CompletedIterations: &completed}},
		{Type: "result", Result: &contracts.StressResult{RequestID: "request-1", TotalCases: 1, CorrectCasesCount: 1}},
	}
	var payload []byte
	for _, record := range records {
		line, err := json.Marshal(record)
		if err != nil {
			t.Fatal(err)
		}
		payload = append(payload, line...)
		payload = append(payload, '\n')
	}

	var progress []contracts.StressProgress
	decoder := newStressStreamDecoder(func(update contracts.StressProgress) error {
		progress = append(progress, update)
		return nil
	})
	for _, chunk := range [][]byte{payload[:17], payload[17:41], payload[41:44], payload[44:]} {
		if _, err := decoder.Write(chunk); err != nil {
			t.Fatalf("Write() error = %v", err)
		}
	}
	result, err := decoder.Finish()
	if err != nil {
		t.Fatalf("Finish() error = %v", err)
	}
	if result.RequestID != "request-1" || result.TotalCases != 1 {
		t.Fatalf("result = %+v", result)
	}
	wantProgress := []contracts.StressProgress{*records[0].Progress, *records[1].Progress}
	if !reflect.DeepEqual(progress, wantProgress) {
		t.Fatalf("progress = %#v, want %#v", progress, wantProgress)
	}
}

func TestDecodeLambdaStreamHandlesPayloadChunksAndCompletion(t *testing.T) {
	reader := &fakeLambdaStreamReader{events: make(chan lambdatypes.InvokeWithResponseStreamResponseEvent, 3)}
	reader.events <- &lambdatypes.InvokeWithResponseStreamResponseEventMemberPayloadChunk{
		Value: lambdatypes.InvokeResponseStreamUpdate{Payload: []byte("{\"type\":\"progress\",\"progress\":{\"stage\":\"stress_running\",\"completedIterations\":1}}\n{\"type\":\"res")},
	}
	reader.events <- &lambdatypes.InvokeWithResponseStreamResponseEventMemberPayloadChunk{
		Value: lambdatypes.InvokeResponseStreamUpdate{Payload: []byte("ult\",\"result\":{\"requestId\":\"request-2\",\"totalCases\":1}}\n")},
	}
	reader.events <- &lambdatypes.InvokeWithResponseStreamResponseEventMemberInvokeComplete{}
	close(reader.events)
	stream := lambda.NewInvokeWithResponseStreamEventStream(func(stream *lambda.InvokeWithResponseStreamEventStream) {
		stream.Reader = reader
	})

	var updates []contracts.StressProgress
	result, err := decodeLambdaResponseStream(stream, func(progress contracts.StressProgress) error {
		updates = append(updates, progress)
		return nil
	})
	if err != nil {
		t.Fatalf("decodeLambdaResponseStream() error = %v", err)
	}
	if result.RequestID != "request-2" || result.TotalCases != 1 {
		t.Fatalf("result = %+v", result)
	}
	if len(updates) != 1 || updates[0].CompletedIterations == nil || *updates[0].CompletedIterations != 1 {
		t.Fatalf("updates = %#v", updates)
	}
}

func TestDecodeLambdaStreamRejectsIncompleteResponse(t *testing.T) {
	reader := &fakeLambdaStreamReader{events: make(chan lambdatypes.InvokeWithResponseStreamResponseEvent, 1)}
	reader.events <- &lambdatypes.InvokeWithResponseStreamResponseEventMemberPayloadChunk{
		Value: lambdatypes.InvokeResponseStreamUpdate{Payload: []byte("{\"type\":\"progress\",\"progress\":{\"stage\":\"finalizing\"}}\n")},
	}
	close(reader.events)
	stream := lambda.NewInvokeWithResponseStreamEventStream(func(stream *lambda.InvokeWithResponseStreamEventStream) {
		stream.Reader = reader
	})

	if _, err := decodeLambdaResponseStream(stream, func(contracts.StressProgress) error { return nil }); err == nil {
		t.Fatal("decodeLambdaResponseStream() error = nil, want missing completion error")
	}
}
