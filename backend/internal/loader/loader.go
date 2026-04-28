package loader

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

const (
	defaultTimeLimitMS = 2000
	defaultMemoryMB    = 256
	authorIndexName    = ".author-index.json"
	typeMetadataName   = "type_metadata.yaml"
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

type CodeFile struct {
	Filename   string
	Language   contracts.Language
	Content    string
	AuthorName string
}

func (f CodeFile) FilenameValue() string {
	return f.Filename
}

type TestcaseFile struct {
	Filename   string
	Content    string
	AuthorName string
}

func (f TestcaseFile) FilenameValue() string {
	return f.Filename
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
	UnknownFiles   []string
	Runnable       bool
}

type TypeMetadata struct {
	Label    string                `json:"label,omitempty"`
	Segments []TypeMetadataSegment `json:"segments,omitempty"`
}

type TypeMetadataSegment struct {
	Label  string                     `json:"label,omitempty"`
	Labels []TypeMetadataSegmentLabel `json:"labels,omitempty"`
}

type TypeMetadataSegmentLabel struct {
	Value string `json:"value"`
	Label string `json:"label"`
}

type Options struct {
	AllowUnknownFiles bool
	AuthorByRelPath   map[string]string
	ProblemType       string
	ExternalID        string
}

type metadataFile struct {
	Title          string            `yaml:"title"`
	ExternalLink   string            `yaml:"externalLink"`
	Authors        map[string]string `yaml:"authors"`
	TimeLimitMS    int               `yaml:"timeLimitMs"`
	MemoryLimitMB  int               `yaml:"memoryLimitMb"`
	IsSpecialJudge bool              `yaml:"isSpecialJudge"`
	Codes          map[string]string `yaml:"codes"`
}

type rawTypeMetadataFile struct {
	SchemaVersion int                      `yaml:"schemaVersion"`
	Label         string                   `yaml:"label"`
	Segments      []rawTypeMetadataSegment `yaml:"segments"`
}

type rawTypeMetadataSegment struct {
	Label  string    `yaml:"label"`
	Labels yaml.Node `yaml:"labels"`
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
		err := walkProblemDirs(typePath, "", func(relPath, problemPath string) {
			problem, err := LoadProblem(problemPath, Options{
				AllowUnknownFiles: true,
				AuthorByRelPath:   authorByRelPath,
				ProblemType:       typeDir.Name(),
				ExternalID:        filepath.ToSlash(relPath),
			})
			if err != nil {
				slog.Warn("problem_load_failed", "path", problemPath, "err", err)
				return
			}
			catalog[[2]string{problem.ProblemType, problem.ExternalID}] = problem
		})
		if err != nil {
			return nil, err
		}
	}
	slog.Info("catalog_built", "problems", len(catalog), "testcase_root", testcaseRoot)
	return catalog, nil
}

func BuildTypeMetadata(testcaseRoot string) (map[string]TypeMetadata, error) {
	metadata := make(map[string]TypeMetadata)
	info, err := os.Stat(testcaseRoot)
	if err != nil {
		if errors.Is(err, os.ErrNotExist) {
			return metadata, nil
		}
		return nil, err
	}
	if !info.IsDir() {
		return nil, fmt.Errorf("testcase root is not a directory: %s", testcaseRoot)
	}

	typeDirs, err := os.ReadDir(testcaseRoot)
	if err != nil {
		return nil, err
	}
	for _, typeDir := range typeDirs {
		if !typeDir.IsDir() {
			continue
		}
		typePath := filepath.Join(testcaseRoot, typeDir.Name())
		typeMeta, err := LoadTypeMetadata(typePath)
		if err != nil {
			return nil, fmt.Errorf("load type metadata %s: %w", typeDir.Name(), err)
		}
		if typeMeta != nil {
			metadata[typeDir.Name()] = *typeMeta
		}
	}
	return metadata, nil
}

func LoadTypeMetadata(typePath string) (*TypeMetadata, error) {
	metadataPath := filepath.Join(typePath, typeMetadataName)
	data, err := os.ReadFile(metadataPath)
	if err != nil {
		if errors.Is(err, os.ErrNotExist) {
			return nil, nil
		}
		return nil, err
	}

	var raw rawTypeMetadataFile
	decoder := yaml.NewDecoder(bytes.NewReader(data))
	decoder.KnownFields(true)
	if err := decoder.Decode(&raw); err != nil {
		return nil, fmt.Errorf("parse type metadata: %w", err)
	}
	if raw.SchemaVersion != 1 {
		return nil, fmt.Errorf("unsupported schemaVersion %d", raw.SchemaVersion)
	}

	metadata := TypeMetadata{
		Label:    raw.Label,
		Segments: make([]TypeMetadataSegment, 0, len(raw.Segments)),
	}
	for _, rawSegment := range raw.Segments {
		segment := TypeMetadataSegment{Label: rawSegment.Label}
		if rawSegment.Labels.Kind != 0 {
			labels, err := parseOrderedSegmentLabels(rawSegment.Labels)
			if err != nil {
				return nil, err
			}
			segment.Labels = labels
		}
		metadata.Segments = append(metadata.Segments, segment)
	}
	return &metadata, nil
}

func parseOrderedSegmentLabels(labelsNode yaml.Node) ([]TypeMetadataSegmentLabel, error) {
	if labelsNode.Kind != yaml.MappingNode {
		return nil, fmt.Errorf("segment labels must be a mapping")
	}
	labels := make([]TypeMetadataSegmentLabel, 0, len(labelsNode.Content)/2)
	for i := 0; i < len(labelsNode.Content); i += 2 {
		keyNode := labelsNode.Content[i]
		valueNode := labelsNode.Content[i+1]
		if keyNode.Kind != yaml.ScalarNode || valueNode.Kind != yaml.ScalarNode {
			return nil, fmt.Errorf("segment labels must map scalar values to scalar labels")
		}
		labels = append(labels, TypeMetadataSegmentLabel{
			Value: keyNode.Value,
			Label: valueNode.Value,
		})
	}
	return labels, nil
}

func walkProblemDirs(dirPath, relPath string, visit func(relPath, problemPath string)) error {
	entries, err := os.ReadDir(dirPath)
	if err != nil {
		return err
	}
	if isProblemDir(entries) {
		visit(relPath, dirPath)
		return nil
	}
	for _, entry := range entries {
		if strings.HasPrefix(entry.Name(), ".") {
			continue
		}
		childPath := filepath.Join(dirPath, entry.Name())
		childRelPath := filepath.Join(relPath, entry.Name())
		if entry.IsDir() {
			if err := walkProblemDirs(childPath, childRelPath, visit); err != nil {
				return err
			}
			continue
		}
		if entry.Type()&os.ModeSymlink == 0 {
			continue
		}
		info, err := os.Stat(childPath)
		if err != nil {
			return err
		}
		if !info.IsDir() {
			continue
		}
		if err := walkProblemDirs(childPath, childRelPath, visit); err != nil {
			return err
		}
	}
	return nil
}

func isProblemDir(entries []os.DirEntry) bool {
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		switch {
		case name == "metadata.yaml" || name == "description.md":
			return true
		case name == "validator.cpp" || name == "checker.cpp":
			return true
		case IsRoleFile(name, "correct"), IsRoleFile(name, "generator"), IsRoleFile(name, "singlegen"):
			return true
		case IsRoleFile(name, "testcase") && strings.EqualFold(filepath.Ext(name), ".txt"):
			return true
		}
	}
	return false
}

func LoadProblem(dirPath string, options Options) (Problem, error) {
	problemType := filepath.Base(filepath.Dir(dirPath))
	externalID := filepath.Base(dirPath)
	if options.ProblemType != "" {
		problemType = options.ProblemType
	}
	if options.ExternalID != "" {
		externalID = options.ExternalID
	}

	meta := metadataFile{TimeLimitMS: defaultTimeLimitMS, MemoryLimitMB: defaultMemoryMB}
	metadataPath := filepath.Join(dirPath, "metadata.yaml")
	if data, err := os.ReadFile(metadataPath); err == nil {
		decoder := yaml.NewDecoder(bytes.NewReader(data))
		decoder.KnownFields(true)
		if err := decoder.Decode(&meta); err != nil {
			return Problem{}, fmt.Errorf("parse metadata: %w", err)
		}
	} else if !errors.Is(err, os.ErrNotExist) {
		return Problem{}, err
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

	seen := map[string]struct{}{}
	entries, err := os.ReadDir(dirPath)
	if err != nil {
		return Problem{}, err
	}
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		seen[name] = struct{}{}
		if name == "metadata.yaml" || name == "description.md" {
			continue
		}
		contentBytes, err := os.ReadFile(filepath.Join(dirPath, name))
		if err != nil {
			return Problem{}, err
		}
		authorName := sourceAuthor(name, meta.Authors, options.AuthorByRelPath, problemType, externalID)
		switch {
		case name == "validator.cpp":
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Validator = &file
		case name == "checker.cpp":
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Checker = &file
		case IsRoleFile(name, "correct"):
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.CorrectCodes = append(problem.CorrectCodes, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case IsRoleFile(name, "generator"):
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Generators = append(problem.Generators, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case IsRoleFile(name, "singlegen"):
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Singlegens = append(problem.Singlegens, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case IsRoleFile(name, "testcase") && strings.EqualFold(filepath.Ext(name), ".txt"):
			problem.Testcases = append(problem.Testcases, TestcaseFile{Filename: name, Content: string(contentBytes), AuthorName: authorName})
		default:
			problem.UnknownFiles = append(problem.UnknownFiles, name)
		}
	}
	for name := range meta.Codes {
		if _, ok := seen[name]; !ok {
			return Problem{}, fmt.Errorf("language override references missing file %q", name)
		}
	}
	for name := range meta.Authors {
		if _, ok := seen[name]; !ok {
			return Problem{}, fmt.Errorf("author override references missing file %q", name)
		}
	}
	if len(problem.UnknownFiles) > 0 && !options.AllowUnknownFiles {
		slices.Sort(problem.UnknownFiles)
		return Problem{}, fmt.Errorf("unrecognized problem files: %s", strings.Join(problem.UnknownFiles, ", "))
	}

	slices.SortFunc(problem.CorrectCodes, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Generators, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Singlegens, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Testcases, func(a, b TestcaseFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.Sort(problem.UnknownFiles)
	problem.Runnable = isRunnableProblem(problem)
	return problem, nil
}

func isRunnableProblem(problem Problem) bool {
	hasCorrect := len(problem.CorrectCodes) > 0
	hasProvider := len(problem.Generators)+len(problem.Singlegens)+len(problem.Testcases) > 0
	hasRequiredChecker := !problem.IsSpecialJudge || problem.Checker != nil
	return hasCorrect && hasProvider && hasRequiredChecker
}

func sourceAuthor(filename string, authors map[string]string, authorByRelPath map[string]string, problemType, externalID string) string {
	if author, ok := authors[filename]; ok {
		return author
	}
	return authorByRelPath[filepath.ToSlash(filepath.Join(problemType, externalID, filename))]
}

func IsRoleFile(filename, role string) bool {
	base := strings.TrimSuffix(filepath.Base(filename), filepath.Ext(filename))
	return base == role || strings.HasPrefix(base, role+"_")
}

func InferLanguage(filename string, overrides map[string]string) (contracts.Language, error) {
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

func CompareExternalID(a, b string) int {
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
	cmd := exec.Command("git", "-C", repoRoot, "log", "--format=__AUTHOR__%an%x00%ae", "--name-only", "--", "testcase")
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
			if _, username, plus := strings.Cut(local, "+"); plus && strings.TrimSpace(username) != "" {
				return strings.TrimSpace(username)
			}
			return strings.TrimSpace(local)
		}
		return strings.TrimSpace(local)
	}
	return strings.TrimSpace(authorName)
}
