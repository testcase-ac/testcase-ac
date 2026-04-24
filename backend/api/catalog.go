package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"os"
	"os/exec"
	"path/filepath"
	"slices"
	"strconv"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"gopkg.in/yaml.v3"
)

var extensionToLang = map[string]contracts.Language{
	".cpp":  contracts.LanguageCpp23,
	".c":    contracts.LanguageC11,
	".py":   contracts.LanguagePython3,
	".java": contracts.LanguageJava,
	".js":   contracts.LanguageNodeJS,
	".go":   contracts.LanguageGolang,
	".kt":   contracts.LanguageKotlin,
	".rs":   contracts.LanguageRust2021,
	".cs":   contracts.LanguageCSharp,
}

const (
	defaultTimeLimitMS = 2000
	defaultMemoryMB    = 256
	authorIndexName    = ".author-index.json"
)

type CodeFile struct {
	Filename   string
	Language   contracts.Language
	Content    string
	AuthorName string
}

type TestcaseFile struct {
	Filename   string
	Content    string
	AuthorName string
}

type Problem struct {
	ProblemType    string
	ExternalID     string
	Title          string
	ExternalLink   string
	TimeLimitMS    int
	MemoryLimitMB  int
	Description    string
	IsSpecialJudge bool
	CorrectCodes   []CodeFile
	Generators     []CodeFile
	Singlegens     []CodeFile
	Validator      *CodeFile
	Checker        *CodeFile
	Testcases      []TestcaseFile
}

type metadataFile struct {
	Title          string            `yaml:"title"`
	ExternalLink   string            `yaml:"externalLink"`
	TimeLimitMS    int               `yaml:"timeLimitMs"`
	MemoryLimitMB  int               `yaml:"memoryLimitMb"`
	IsSpecialJudge bool              `yaml:"isSpecialJudge"`
	Codes          map[string]string `yaml:"codes"`
}

func BuildCatalog(testcaseRoot string) (map[[2]string]Problem, error) {
	catalog := make(map[[2]string]Problem)
	info, err := os.Stat(testcaseRoot)
	if err != nil {
		if errors.Is(err, os.ErrNotExist) {
			slog.Warn("testcase_root_missing", "testcase_root", testcaseRoot)
			return catalog, nil
		}
		return nil, err
	}
	if !info.IsDir() {
		return nil, fmt.Errorf("testcase root is not a directory: %s", testcaseRoot)
	}

	authorByRelPath := loadAuthorIndex(testcaseRoot)
	typeDirs, err := os.ReadDir(testcaseRoot)
	if err != nil {
		return nil, err
	}
	for _, typeDir := range typeDirs {
		if !typeDir.IsDir() {
			continue
		}
		typePath := filepath.Join(testcaseRoot, typeDir.Name())
		problemDirs, err := os.ReadDir(typePath)
		if err != nil {
			return nil, err
		}
		for _, problemDir := range problemDirs {
			if !problemDir.IsDir() {
				continue
			}
			problemPath := filepath.Join(typePath, problemDir.Name())
			problem, err := loadProblem(problemPath, authorByRelPath)
			if err != nil {
				slog.Warn("problem_load_failed", "path", problemPath, "err", err)
				continue
			}
			catalog[[2]string{problem.ProblemType, problem.ExternalID}] = problem
		}
	}
	slog.Info("catalog_built", "problems", len(catalog), "testcase_root", testcaseRoot)
	return catalog, nil
}

func loadProblem(dirPath string, authorByRelPath map[string]string) (Problem, error) {
	problemType := filepath.Base(filepath.Dir(dirPath))
	externalID := filepath.Base(dirPath)

	meta := metadataFile{
		TimeLimitMS:   defaultTimeLimitMS,
		MemoryLimitMB: defaultMemoryMB,
	}
	metadataPath := filepath.Join(dirPath, "metadata.yaml")
	if data, err := os.ReadFile(metadataPath); err == nil {
		if err := yaml.Unmarshal(data, &meta); err != nil {
			return Problem{}, fmt.Errorf("parse metadata: %w", err)
		}
	}
	if meta.Codes == nil {
		meta.Codes = map[string]string{}
	}

	descriptionBytes, err := os.ReadFile(filepath.Join(dirPath, "description.md"))
	description := ""
	if err == nil {
		description = string(descriptionBytes)
	} else if !errors.Is(err, os.ErrNotExist) {
		return Problem{}, err
	}

	problem := Problem{
		ProblemType:    problemType,
		ExternalID:     externalID,
		Title:          meta.Title,
		ExternalLink:   meta.ExternalLink,
		TimeLimitMS:    meta.TimeLimitMS,
		MemoryLimitMB:  meta.MemoryLimitMB,
		Description:    description,
		IsSpecialJudge: meta.IsSpecialJudge,
	}

	entries, err := os.ReadDir(dirPath)
	if err != nil {
		return Problem{}, err
	}
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		if name == "metadata.yaml" || name == "description.md" {
			continue
		}
		contentBytes, err := os.ReadFile(filepath.Join(dirPath, name))
		if err != nil {
			return Problem{}, err
		}
		authorName := authorByRelPath[filepath.ToSlash(filepath.Join(problemType, externalID, name))]
		switch {
		case name == "validator.cpp":
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Validator = &file
		case name == "checker.cpp":
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Checker = &file
		case strings.HasPrefix(name, "correct"):
			lang, err := inferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.CorrectCodes = append(problem.CorrectCodes, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case strings.HasPrefix(name, "generator"):
			lang, err := inferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Generators = append(problem.Generators, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case strings.HasPrefix(name, "singlegen"):
			lang, err := inferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Singlegens = append(problem.Singlegens, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case strings.HasPrefix(name, "testcase") && strings.HasSuffix(name, ".txt"):
			problem.Testcases = append(problem.Testcases, TestcaseFile{Filename: name, Content: string(contentBytes), AuthorName: authorName})
		default:
			slog.Warn("unrecognized_problem_file", "file", name, "dir", dirPath)
		}
	}

	slices.SortFunc(problem.CorrectCodes, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Generators, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Singlegens, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Testcases, func(a, b TestcaseFile) int { return strings.Compare(a.Filename, b.Filename) })

	return problem, nil
}

func inferLanguage(filename string, overrides map[string]string) (contracts.Language, error) {
	if rawLang, ok := overrides[filename]; ok {
		lang := contracts.Language(rawLang)
		if !contracts.IsSupportedLanguage(lang) {
			return "", fmt.Errorf("unsupported language override %q for %q", rawLang, filename)
		}
		return lang, nil
	}
	lang, ok := extensionToLang[strings.ToLower(filepath.Ext(filename))]
	if !ok {
		return "", fmt.Errorf("unsupported extension for %q", filename)
	}
	return lang, nil
}

func loadAuthorIndex(testcaseRoot string) map[string]string {
	manifestPath := filepath.Join(testcaseRoot, authorIndexName)
	data, err := os.ReadFile(manifestPath)
	if err == nil {
		var authorByRelPath map[string]string
		if err := json.Unmarshal(data, &authorByRelPath); err != nil {
			slog.Warn("author_index_parse_failed", "path", manifestPath, "err", err)
		} else {
			return authorByRelPath
		}
	} else if !errors.Is(err, os.ErrNotExist) {
		slog.Warn("author_index_read_failed", "path", manifestPath, "err", err)
	}
	return buildGitAuthorIndex(testcaseRoot)
}

func buildGitAuthorIndex(testcaseRoot string) map[string]string {
	repoRoot := filepath.Dir(testcaseRoot)
	if _, err := os.Stat(filepath.Join(repoRoot, ".git")); err != nil {
		return map[string]string{}
	}
	cmd := exec.Command(
		"git", "-C", repoRoot, "log",
		"--format=__AUTHOR__%an%x00%ae",
		"--name-only",
		"--", "testcase",
	)
	output, err := cmd.Output()
	if err != nil {
		slog.Warn("git_author_index_build_failed", "testcase_root", testcaseRoot, "err", err)
		return map[string]string{}
	}

	authorByRelPath := make(map[string]string)
	currentAuthor := ""
	for _, rawLine := range bytes.Split(output, []byte{'\n'}) {
		line := strings.TrimSpace(string(rawLine))
		if line == "" {
			continue
		}
		if strings.HasPrefix(line, "__AUTHOR__") {
			payload := strings.TrimPrefix(line, "__AUTHOR__")
			authorName, authorEmail, _ := strings.Cut(payload, "\x00")
			currentAuthor = gitContributorLabel(authorName, authorEmail)
			continue
		}
		if currentAuthor == "" || !strings.HasPrefix(line, "testcase/") {
			continue
		}
		relPath := strings.TrimPrefix(line, "testcase/")
		if _, exists := authorByRelPath[relPath]; !exists {
			authorByRelPath[relPath] = currentAuthor
		}
	}
	return authorByRelPath
}

func gitContributorLabel(authorName, authorEmail string) string {
	email := strings.TrimSpace(authorEmail)
	if email != "" {
		local, domain, found := strings.Cut(email, "@")
		if found && domain == "users.noreply.github.com" {
			if _, username, plus := strings.Cut(local, "+"); plus {
				if strings.TrimSpace(username) != "" {
					return strings.TrimSpace(username)
				}
			}
			return strings.TrimSpace(local)
		}
		return strings.TrimSpace(local)
	}
	return strings.TrimSpace(authorName)
}

func sortProblemSummaries(items []ProblemSummary) {
	slices.SortFunc(items, func(a, b ProblemSummary) int {
		if a.ProblemType != b.ProblemType {
			return strings.Compare(a.ProblemType, b.ProblemType)
		}
		return compareExternalID(a.ExternalID, b.ExternalID)
	})
}

func compareExternalID(a, b string) int {
	ai, aErr := strconv.Atoi(a)
	bi, bErr := strconv.Atoi(b)
	switch {
	case aErr == nil && bErr == nil:
		if ai != bi {
			return ai - bi
		}
		return strings.Compare(a, b)
	case aErr == nil:
		return -1
	case bErr == nil:
		return 1
	default:
		return strings.Compare(a, b)
	}
}
