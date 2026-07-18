package main

import (
	"context"
	"database/sql"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"net/url"
	"strconv"
	"strings"
	"time"

	_ "modernc.org/sqlite"
)

const statsTimeLayout = "2006-01-02T15:04:05.000000000Z"

var errStatsDBPathRequired = errors.New("STATS_DB_PATH must be set")

// StatsStore keeps the durable dispatch ledger used by public statistics.
type StatsStore struct {
	db *sql.DB
}

type StatsDispatch struct {
	RequestID              string
	ProblemType            string
	ExternalID             string
	DispatchedAt           time.Time
	TargetLanguage         *string
	Iterations             *int
	TextProviderCount      *int
	GeneratorProviderCount *int
	SinglegenProviderCount *int
	CheckerUsed            *bool
}

type StatsTerminal struct {
	RequestID            string
	TerminalAt           time.Time
	Outcome              string
	StressStatus         *string
	ErrorType            *string
	RuntimeSeconds       *float64
	TotalCases           *int
	WrongCases           *int
	ExecutionFailedCases *int
}

type StatsBucket struct {
	StartUTC time.Time `json:"startUtc"`
	Count    int64     `json:"count"`
}

type StatsSnapshot struct {
	Total         int64
	Buckets       []StatsBucket
	ProblemCounts map[[2]string]int64
}

type ReconciliationState struct {
	JournalCursor string
}

func OpenStatsStore(path string) (*StatsStore, error) {
	if strings.TrimSpace(path) == "" {
		return nil, errStatsDBPathRequired
	}
	values := url.Values{}
	values.Add("_pragma", "busy_timeout(250)")
	values.Add("_pragma", "journal_mode(WAL)")
	dsn := (&url.URL{Scheme: "file", Path: path, RawQuery: values.Encode()}).String()
	db, err := sql.Open("sqlite", dsn)
	if err != nil {
		return nil, err
	}
	db.SetMaxOpenConns(4)
	store := &StatsStore{db: db}
	if err := store.initialize(context.Background()); err != nil {
		_ = db.Close()
		return nil, err
	}
	return store, nil
}

func (s *StatsStore) initialize(ctx context.Context) error {
	var version int
	if err := s.db.QueryRowContext(ctx, "PRAGMA user_version").Scan(&version); err != nil {
		return err
	}
	if version == 1 {
		return nil
	}
	if version != 0 {
		return fmt.Errorf("unsupported statistics schema version %d", version)
	}

	tx, err := s.db.BeginTx(ctx, nil)
	if err != nil {
		return err
	}
	defer tx.Rollback()

	for _, statement := range []string{
		`CREATE TABLE IF NOT EXISTS executions (
            request_id TEXT PRIMARY KEY,
            problem_type TEXT NOT NULL,
            external_id TEXT NOT NULL,
            dispatched_at_utc TEXT NOT NULL,
            terminal_at_utc TEXT,
            outcome TEXT,
            target_language TEXT,
            iterations INTEGER,
            text_provider_count INTEGER,
            generator_provider_count INTEGER,
            singlegen_provider_count INTEGER,
            checker_used INTEGER,
            stress_status TEXT,
            error_type TEXT,
            runtime_seconds REAL,
            total_cases INTEGER,
            wrong_cases INTEGER,
            execution_failed_cases INTEGER
        )`,
		`CREATE INDEX IF NOT EXISTS executions_dispatched_at_idx ON executions(dispatched_at_utc)`,
		`CREATE INDEX IF NOT EXISTS executions_problem_idx ON executions(problem_type, external_id)`,
		`CREATE TABLE IF NOT EXISTS reconciliation_state (
            id INTEGER PRIMARY KEY CHECK (id = 1),
            journal_cursor TEXT,
            last_reconciled_at_utc TEXT
        )`,
		`PRAGMA user_version = 1`,
	} {
		if _, err := tx.ExecContext(ctx, statement); err != nil {
			return err
		}
	}
	return tx.Commit()
}

func (s *StatsStore) Close() error {
	return s.db.Close()
}

func (s *StatsStore) RecordDispatch(ctx context.Context, dispatch StatsDispatch) error {
	_, err := s.db.ExecContext(ctx, dispatchInsertSQL, dispatchArgs(dispatch)...)
	return err
}

const dispatchInsertSQL = `INSERT INTO executions (
    request_id, problem_type, external_id, dispatched_at_utc, target_language,
    iterations, text_provider_count, generator_provider_count,
    singlegen_provider_count, checker_used
) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
ON CONFLICT(request_id) DO NOTHING`

func dispatchArgs(dispatch StatsDispatch) []any {
	return []any{
		dispatch.RequestID,
		dispatch.ProblemType,
		dispatch.ExternalID,
		formatStatsTime(dispatch.DispatchedAt),
		dispatch.TargetLanguage,
		dispatch.Iterations,
		dispatch.TextProviderCount,
		dispatch.GeneratorProviderCount,
		dispatch.SinglegenProviderCount,
		dispatch.CheckerUsed,
	}
}

func (s *StatsStore) RecordTerminal(ctx context.Context, terminal StatsTerminal) error {
	_, err := s.db.ExecContext(ctx, terminalUpdateSQL, terminalArgs(terminal)...)
	return err
}

const terminalUpdateSQL = `UPDATE executions SET
    terminal_at_utc = ?, outcome = ?, stress_status = ?, error_type = ?,
    runtime_seconds = ?, total_cases = ?, wrong_cases = ?, execution_failed_cases = ?
WHERE request_id = ?`

func terminalArgs(terminal StatsTerminal) []any {
	return []any{
		formatStatsTime(terminal.TerminalAt),
		terminal.Outcome,
		terminal.StressStatus,
		terminal.ErrorType,
		terminal.RuntimeSeconds,
		terminal.TotalCases,
		terminal.WrongCases,
		terminal.ExecutionFailedCases,
		terminal.RequestID,
	}
}

func (s *StatsStore) ProblemTotal(ctx context.Context, problemType, externalID string) (int64, error) {
	var total int64
	err := s.db.QueryRowContext(ctx,
		`SELECT COUNT(*) FROM executions WHERE problem_type = ? AND external_id = ?`,
		problemType, externalID,
	).Scan(&total)
	return total, err
}

func (s *StatsStore) Snapshot(ctx context.Context, now time.Time) (StatsSnapshot, error) {
	now = now.UTC()
	start := now.Truncate(time.Hour).Add(-167 * time.Hour)
	rows, err := s.db.QueryContext(ctx,
		`SELECT dispatched_at_utc, problem_type, external_id
         FROM executions
         WHERE dispatched_at_utc >= ? AND dispatched_at_utc <= ?`,
		formatStatsTime(start), formatStatsTime(now),
	)
	if err != nil {
		return StatsSnapshot{}, err
	}
	defer rows.Close()

	snapshot := StatsSnapshot{
		Buckets:       make([]StatsBucket, 168),
		ProblemCounts: make(map[[2]string]int64),
	}
	for i := range snapshot.Buckets {
		snapshot.Buckets[i].StartUTC = start.Add(time.Duration(i) * time.Hour)
	}
	for rows.Next() {
		var rawTime, problemType, externalID string
		if err := rows.Scan(&rawTime, &problemType, &externalID); err != nil {
			return StatsSnapshot{}, err
		}
		dispatchedAt, err := time.Parse(statsTimeLayout, rawTime)
		if err != nil {
			return StatsSnapshot{}, err
		}
		bucket := int(dispatchedAt.Sub(start) / time.Hour)
		if bucket < 0 || bucket >= len(snapshot.Buckets) {
			continue
		}
		snapshot.Total++
		snapshot.Buckets[bucket].Count++
		snapshot.ProblemCounts[[2]string{problemType, externalID}]++
	}
	return snapshot, rows.Err()
}

func (s *StatsStore) ReconciliationState(ctx context.Context) (ReconciliationState, error) {
	var cursor sql.NullString
	err := s.db.QueryRowContext(ctx,
		`SELECT journal_cursor FROM reconciliation_state WHERE id = 1`,
	).Scan(&cursor)
	if errors.Is(err, sql.ErrNoRows) {
		return ReconciliationState{}, nil
	}
	if err != nil {
		return ReconciliationState{}, err
	}
	return ReconciliationState{JournalCursor: cursor.String}, nil
}

func (s *StatsStore) reconcileJournal(ctx context.Context, reader io.Reader, reconciledAt time.Time, finish func() error) error {
	state, err := s.ReconciliationState(ctx)
	if err != nil {
		return err
	}
	tx, err := s.db.BeginTx(ctx, nil)
	if err != nil {
		return err
	}
	defer tx.Rollback()

	lastCursor := state.JournalCursor
	decoder := json.NewDecoder(reader)
	for {
		var entry journalEntry
		if err := decoder.Decode(&entry); errors.Is(err, io.EOF) {
			break
		} else if err != nil {
			return err
		}
		if entry.Cursor != "" {
			lastCursor = entry.Cursor
		}
		message, ok := entry.message()
		if !ok {
			continue
		}
		at, err := entry.timestamp()
		if err != nil {
			return err
		}
		switch message.Message {
		case "stress_dispatch":
			if message.RequestID == "" || message.ProblemType == "" || message.ExternalID == "" {
				continue
			}
			dispatch := message.dispatch(at)
			if _, err := tx.ExecContext(ctx, dispatchInsertSQL, dispatchArgs(dispatch)...); err != nil {
				return err
			}
		case "stress_terminal":
			if message.RequestID == "" || message.Outcome == "" {
				continue
			}
			terminal := message.terminal(at)
			if _, err := tx.ExecContext(ctx, terminalUpdateSQL, terminalArgs(terminal)...); err != nil {
				return err
			}
		}
	}
	if finish != nil {
		if err := finish(); err != nil {
			return err
		}
	}
	if _, err := tx.ExecContext(ctx, `INSERT INTO reconciliation_state (
        id, journal_cursor, last_reconciled_at_utc
    ) VALUES (1, ?, ?)
    ON CONFLICT(id) DO UPDATE SET
        journal_cursor = excluded.journal_cursor,
        last_reconciled_at_utc = excluded.last_reconciled_at_utc`,
		lastCursor, formatStatsTime(reconciledAt),
	); err != nil {
		return err
	}
	return tx.Commit()
}

type journalEntry struct {
	Cursor            string          `json:"__CURSOR"`
	RealtimeTimestamp string          `json:"__REALTIME_TIMESTAMP"`
	Message           json.RawMessage `json:"MESSAGE"`
}

func (entry journalEntry) message() (journalMessage, bool) {
	var raw string
	if err := json.Unmarshal(entry.Message, &raw); err != nil {
		return journalMessage{}, false
	}
	var message journalMessage
	if err := json.Unmarshal([]byte(raw), &message); err != nil {
		return journalMessage{}, false
	}
	return message, true
}

func (entry journalEntry) timestamp() (time.Time, error) {
	microseconds, err := strconv.ParseInt(entry.RealtimeTimestamp, 10, 64)
	if err != nil {
		return time.Time{}, err
	}
	return time.UnixMicro(microseconds).UTC(), nil
}

type journalMessage struct {
	Message                string   `json:"msg"`
	RequestID              string   `json:"request_id"`
	ProblemType            string   `json:"problem_type"`
	ExternalID             string   `json:"external_id"`
	TargetLanguage         *string  `json:"target_language"`
	Iterations             *int     `json:"iterations"`
	TextProviderCount      *int     `json:"text_provider_count"`
	GeneratorProviderCount *int     `json:"generator_provider_count"`
	SinglegenProviderCount *int     `json:"singlegen_provider_count"`
	CheckerUsed            *bool    `json:"checker_used"`
	Outcome                string   `json:"outcome"`
	StressStatus           *string  `json:"stress_status"`
	ErrorType              *string  `json:"error_type"`
	RuntimeSeconds         *float64 `json:"runtime_seconds"`
	TotalCases             *int     `json:"total_cases"`
	WrongCases             *int     `json:"wrong_cases"`
	ExecutionFailedCases   *int     `json:"execution_failed_cases"`
}

func (message journalMessage) dispatch(at time.Time) StatsDispatch {
	return StatsDispatch{
		RequestID: message.RequestID, ProblemType: message.ProblemType,
		ExternalID: message.ExternalID, DispatchedAt: at,
		TargetLanguage: message.TargetLanguage, Iterations: message.Iterations,
		TextProviderCount:      message.TextProviderCount,
		GeneratorProviderCount: message.GeneratorProviderCount,
		SinglegenProviderCount: message.SinglegenProviderCount,
		CheckerUsed:            message.CheckerUsed,
	}
}

func (message journalMessage) terminal(at time.Time) StatsTerminal {
	return StatsTerminal{
		RequestID: message.RequestID, TerminalAt: at, Outcome: message.Outcome,
		StressStatus: message.StressStatus, ErrorType: message.ErrorType,
		RuntimeSeconds: message.RuntimeSeconds, TotalCases: message.TotalCases,
		WrongCases: message.WrongCases, ExecutionFailedCases: message.ExecutionFailedCases,
	}
}

func formatStatsTime(value time.Time) string {
	return value.UTC().Format(statsTimeLayout)
}
