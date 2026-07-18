package main

// Request flow: main.go -> runtime.go -> handler.go -> stress.go.
// This file configures the process and starts the AWS Lambda or local runtime.

import (
	"errors"
	"log/slog"
	"net/http"
	"os"
	"time"

	"github.com/aws/aws-lambda-go/lambda"
)

func main() {
	slog.SetDefault(slog.New(slog.NewJSONHandler(os.Stdout, nil)))
	// prod: AWS_LAMBDA_RUNTIME_API is set by AWS Lambda runtime.
	// setup default HTTP transport to support streaming response in a way recognized by AWS Lambda runtime.
	if os.Getenv("AWS_LAMBDA_RUNTIME_API") != "" {
		installStreamingTransport()
		lambda.Start(lambdaHandler)
		return
	}
	// local: run as a local HTTP server in 8080.
	// `dev.sh` runs the 8080 server in docker, and maps 8080 to STRESSER_PORT in host machine.
	slog.Info("local_stresser_ready", "addr", ":8080")
	server := &http.Server{Addr: ":8080", Handler: localHandler(), ReadHeaderTimeout: 5 * time.Second}
	if err := server.ListenAndServe(); err != nil && !errors.Is(err, http.ErrServerClosed) {
		slog.Error("local_stresser_failed", "err", err)
		os.Exit(1)
	}
}
