package main

import (
	"context"
	"errors"
	"log/slog"
	"net/http"
	"os"
	"os/signal"
	"runtime"
	"syscall"
	"time"
)

const shutdownTimeout = 180 * time.Second

func main() {
	logger := slog.New(slog.NewJSONHandler(os.Stdout, nil))
	slog.SetDefault(logger)

	settings, err := LoadSettings()
	if err != nil {
		fatal(err)
	}
	testcaseRoot, err := ResolveTestcaseRoot(settings)
	if err != nil {
		fatal(err)
	}

	buildStarted := time.Now()
	catalog, err := BuildCatalog(testcaseRoot)
	if err != nil {
		fatal(err)
	}
	typeMetadata, err := BuildTypeMetadata(testcaseRoot)
	if err != nil {
		fatal(err)
	}
	stresser, err := MakeStresserClient(context.Background(), settings)
	if err != nil {
		fatal(err)
	}

	var mem runtime.MemStats
	runtime.ReadMemStats(&mem)
	slog.Info(
		"backend_ready",
		"mode", settings.StresserMode,
		"problems", len(catalog),
		"problem_types_with_metadata", len(typeMetadata),
		"catalog_build_ms", time.Since(buildStarted).Milliseconds(),
		"heap_alloc_mb", float64(mem.Alloc)/1024.0/1024.0,
	)

	app := NewAppWithTypeMetadata(settings, catalog, typeMetadata, stresser)
	server := &http.Server{
		Addr:         settings.HTTPAddr,
		Handler:      app.Handler(),
		ReadTimeout:  15 * time.Second,
		WriteTimeout: 180 * time.Second,
		IdleTimeout:  60 * time.Second,
	}
	slog.Info("listening", "addr", settings.HTTPAddr)
	if err := runServer(server); err != nil {
		fatal(err)
	}
}

func fatal(err error) {
	slog.Error("fatal", "err", err)
	os.Exit(1)
}

func runServer(server *http.Server) error {
	errCh := make(chan error, 1)
	go func() {
		errCh <- server.ListenAndServe()
	}()

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, os.Interrupt, syscall.SIGTERM)
	defer signal.Stop(sigCh)

	select {
	case err := <-errCh:
		if errors.Is(err, http.ErrServerClosed) {
			return nil
		}
		return err
	case sig := <-sigCh:
		slog.Info("shutdown_started", "signal", sig.String(), "timeout_seconds", shutdownTimeout.Seconds())
	}

	ctx, cancel := context.WithTimeout(context.Background(), shutdownTimeout)
	defer cancel()
	if err := server.Shutdown(ctx); err != nil {
		slog.Error("shutdown_failed", "err", err)
		_ = server.Close()
		return err
	}
	slog.Info("shutdown_complete")
	return nil
}
