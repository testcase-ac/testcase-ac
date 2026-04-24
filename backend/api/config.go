package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
)

var localhostOriginRegex = regexp.MustCompile(`^http://(localhost|127\.0\.0\.1):517[3-9]$`)

type Settings struct {
	TestcaseLocalPath          string
	StresserMode               string
	StresserLocalEndpoint      string
	StresserLambdaFunctionName string
	AWSRegion                  string
	RateLimitMax               int
	RateLimitWindowS           float64
	CORSAllowOrigins           []string
	HTTPAddr                   string
}

func LoadSettings() (Settings, error) {
	_ = loadDotEnv(".env")

	settings := Settings{
		TestcaseLocalPath:          getEnv("TESTCASE_LOCAL_PATH", ""),
		StresserMode:               getEnv("STRESSER_MODE", "local_docker"),
		StresserLocalEndpoint:      getEnv("STRESSER_LOCAL_ENDPOINT", "http://localhost:9000/2015-03-31/functions/function/invocations"),
		StresserLambdaFunctionName: getEnv("STRESSER_LAMBDA_FUNCTION_NAME", "testcase-ac-stresser"),
		AWSRegion:                  getEnv("AWS_REGION", "ap-northeast-2"),
		RateLimitMax:               getEnvInt("RATE_LIMIT_MAX", 5),
		RateLimitWindowS:           getEnvFloat("RATE_LIMIT_WINDOW_S", 10.0),
		CORSAllowOrigins:           splitCSV(getEnv("CORS_ALLOW_ORIGINS", "http://localhost:5173,http://127.0.0.1:5173,https://testcase-ac.github.io,https://next.testcase.ac,https://testcase.ac")),
		HTTPAddr:                   getEnv("HTTP_ADDR", "127.0.0.1:8000"),
	}

	switch settings.StresserMode {
	case "local_docker", "lambda":
	default:
		return Settings{}, fmt.Errorf("invalid STRESSER_MODE: %s", settings.StresserMode)
	}

	return settings, nil
}

func ResolveTestcaseRoot(settings Settings) (string, error) {
	if strings.TrimSpace(settings.TestcaseLocalPath) == "" {
		return "", fmt.Errorf("TESTCASE_LOCAL_PATH must be set")
	}
	return filepath.Join(settings.TestcaseLocalPath, "testcase"), nil
}

func OriginAllowed(settings Settings, origin string) bool {
	if origin == "" {
		return false
	}
	for _, allowed := range settings.CORSAllowOrigins {
		if origin == allowed {
			return true
		}
	}
	return localhostOriginRegex.MatchString(origin)
}

func splitCSV(raw string) []string {
	if strings.TrimSpace(raw) == "" {
		return nil
	}
	parts := strings.Split(raw, ",")
	out := make([]string, 0, len(parts))
	for _, part := range parts {
		part = strings.TrimSpace(part)
		if part != "" {
			out = append(out, part)
		}
	}
	return out
}

func getEnv(key, fallback string) string {
	if value, ok := os.LookupEnv(key); ok {
		return value
	}
	return fallback
}

func getEnvInt(key string, fallback int) int {
	value, ok := os.LookupEnv(key)
	if !ok || strings.TrimSpace(value) == "" {
		return fallback
	}
	parsed, err := strconv.Atoi(value)
	if err != nil {
		return fallback
	}
	return parsed
}

func getEnvFloat(key string, fallback float64) float64 {
	value, ok := os.LookupEnv(key)
	if !ok || strings.TrimSpace(value) == "" {
		return fallback
	}
	parsed, err := strconv.ParseFloat(value, 64)
	if err != nil {
		return fallback
	}
	return parsed
}

func loadDotEnv(path string) error {
	file, err := os.Open(path)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}
		key, value, ok := strings.Cut(line, "=")
		if !ok {
			continue
		}
		key = strings.TrimSpace(key)
		if key == "" {
			continue
		}
		value = strings.TrimSpace(value)
		value = strings.Trim(value, `"'`)
		if _, exists := os.LookupEnv(key); !exists {
			_ = os.Setenv(key, value)
		}
	}
	return scanner.Err()
}
