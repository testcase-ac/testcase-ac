package main

import (
	"context"
	"encoding/json"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type auditCaseProvider struct {
	Kind contracts.CaseProviderType `json:"kind"`
	ID   string                     `json:"id"`
}

type auditFailureSample struct {
	contracts.GeneratedBy
	Verdict *contracts.Verdict `json:"verdict,omitempty"`
}

func (s *StatsStore) RecordSubmission(ctx context.Context, dispatch StatsDispatch, event contracts.StressEvent, response StressResponse, testcaseRevision string) error {
	providers := make([]auditCaseProvider, 0, len(event.CaseProviders))
	for _, provider := range event.CaseProviders {
		providers = append(providers, auditCaseProvider{Kind: provider.Type, ID: provider.ID})
	}
	providersJSON, err := json.Marshal(providers)
	if err != nil {
		return err
	}
	samples := make([]auditFailureSample, 0, len(response.WrongCases)+len(response.ExecutionFailedCases))
	for _, sample := range response.WrongCases {
		samples = append(samples, auditFailureSample{GeneratedBy: sample.GeneratedBy, Verdict: sample.Verdict})
	}
	for _, sample := range response.ExecutionFailedCases {
		samples = append(samples, auditFailureSample{GeneratedBy: sample.GeneratedBy, Verdict: new(sample.Reason)})
	}
	samplesJSON, err := json.Marshal(samples)
	if err != nil {
		return err
	}
	_, err = s.db.ExecContext(ctx, `INSERT INTO submissions (
    request_id, submitted_at_utc, problem_type, external_id, testcase_revision,
    target_language, target_source, reference_filename, providers_json, iterations,
    runtime_limit_seconds, status, total_cases, failure_samples_json
) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
ON CONFLICT(request_id) DO NOTHING`,
		dispatch.RequestID, formatStatsTime(dispatch.DispatchedAt), dispatch.ProblemType, dispatch.ExternalID, testcaseRevision,
		event.TargetCodeLang, event.TargetCode, event.CorrectCodeFilename, string(providersJSON), event.Iterations,
		event.TotalRuntimeLimitSeconds, response.Status, response.TotalCases, string(samplesJSON),
	)
	return err
}
