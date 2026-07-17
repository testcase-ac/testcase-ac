package loader

import (
	"bytes"
	"errors"
	"fmt"
	"io/fs"
	"log/slog"
	"os"
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

type AnswerFile struct {
	Filename   string
	Content    string
	AuthorName string
	// TargetProviderFilename is the testcase or singlegen file answered by this file.
	TargetProviderFilename string
}

type IgnoredOutputOnlyFile struct {
	Filename string
	Role     string
}

type Problem struct {
	ProblemType            string
	ExternalID             string
	Title                  string
	ExternalLink           string
	TimeLimitMS            int
	MemoryLimitMB          int
	Description            string
	IsSpecialJudge         bool
	OutputOnly             bool
	CorrectCodes           []CodeFile
	RejectedCodes          []CodeFile
	Generators             []CodeFile
	Singlegens             []CodeFile
	Validator              *CodeFile
	Checker                *CodeFile
	Testcases              []TestcaseFile
	AnswerFiles            []AnswerFile
	IgnoredOutputOnlyFiles []IgnoredOutputOnlyFile
	UnknownFiles           []string
	Runnable               bool
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

type filesystem interface {
	Stat(string) (fs.FileInfo, error)
	ReadDir(string) ([]fs.DirEntry, error)
	ReadFile(string) ([]byte, error)
}

type problemLoader struct {
	files filesystem
}

type osFilesystem struct{}

func (osFilesystem) Stat(path string) (fs.FileInfo, error) {
	return os.Stat(path)
}

func (osFilesystem) ReadDir(path string) ([]fs.DirEntry, error) {
	return os.ReadDir(path)
}

func (osFilesystem) ReadFile(path string) ([]byte, error) {
	return os.ReadFile(path)
}

type metadataFile struct {
	Title          string            `yaml:"title"`
	ExternalLink   string            `yaml:"externalLink"`
	Authors        map[string]string `yaml:"authors"`
	TimeLimitMS    int               `yaml:"timeLimitMs"`
	MemoryLimitMB  int               `yaml:"memoryLimitMb"`
	IsSpecialJudge bool              `yaml:"isSpecialJudge"`
	OutputOnly     bool              `yaml:"outputOnly"`
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

func BuildCatalog(testcaseRoot string, authorByRelPath map[string]string) (map[[2]string]Problem, error) {
	return newProblemLoader().buildCatalog(testcaseRoot, authorByRelPath)
}

func BuildTypeMetadata(testcaseRoot string) (map[string]TypeMetadata, error) {
	return newProblemLoader().buildTypeMetadata(testcaseRoot)
}

func LoadTypeMetadata(typePath string) (*TypeMetadata, error) {
	return newProblemLoader().loadTypeMetadata(typePath)
}

func LoadProblem(dirPath string, options Options) (Problem, error) {
	return newProblemLoader().loadProblem(dirPath, options)
}

func newProblemLoader() problemLoader {
	return problemLoader{
		files: osFilesystem{},
	}
}

func (l problemLoader) buildCatalog(testcaseRoot string, authorByRelPath map[string]string) (map[[2]string]Problem, error) {
	catalog := make(map[[2]string]Problem)
	info, err := l.files.Stat(testcaseRoot)
	if err != nil {
		if errors.Is(err, fs.ErrNotExist) {
			slog.Warn("testcase_root_missing", "testcase_root", testcaseRoot)
			return catalog, nil
		}
		return nil, err
	}
	if !info.IsDir() {
		return nil, fmt.Errorf("testcase root is not a directory: %s", testcaseRoot)
	}

	typeDirs, err := l.files.ReadDir(testcaseRoot)
	if err != nil {
		return nil, err
	}
	for _, typeDir := range typeDirs {
		if !typeDir.IsDir() {
			continue
		}
		typePath := filepath.Join(testcaseRoot, typeDir.Name())
		err := l.walkProblemDirs(typePath, "", func(relPath, problemPath string) {
			problem, err := l.loadProblem(problemPath, Options{
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

func (l problemLoader) buildTypeMetadata(testcaseRoot string) (map[string]TypeMetadata, error) {
	metadata := make(map[string]TypeMetadata)
	info, err := l.files.Stat(testcaseRoot)
	if err != nil {
		if errors.Is(err, fs.ErrNotExist) {
			return metadata, nil
		}
		return nil, err
	}
	if !info.IsDir() {
		return nil, fmt.Errorf("testcase root is not a directory: %s", testcaseRoot)
	}

	typeDirs, err := l.files.ReadDir(testcaseRoot)
	if err != nil {
		return nil, err
	}
	for _, typeDir := range typeDirs {
		if !typeDir.IsDir() {
			continue
		}
		typePath := filepath.Join(testcaseRoot, typeDir.Name())
		typeMeta, err := l.loadTypeMetadata(typePath)
		if err != nil {
			return nil, fmt.Errorf("load type metadata %s: %w", typeDir.Name(), err)
		}
		if typeMeta != nil {
			metadata[typeDir.Name()] = *typeMeta
		}
	}
	return metadata, nil
}

func (l problemLoader) loadTypeMetadata(typePath string) (*TypeMetadata, error) {
	metadataPath := filepath.Join(typePath, typeMetadataName)
	data, err := l.files.ReadFile(metadataPath)
	if err != nil {
		if errors.Is(err, fs.ErrNotExist) {
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

func (l problemLoader) walkProblemDirs(dirPath, relPath string, visit func(relPath, problemPath string)) error {
	entries, err := l.files.ReadDir(dirPath)
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
			if err := l.walkProblemDirs(childPath, childRelPath, visit); err != nil {
				return err
			}
			continue
		}
		if entry.Type()&fs.ModeSymlink == 0 {
			continue
		}
		info, err := l.files.Stat(childPath)
		if err != nil {
			return err
		}
		if !info.IsDir() {
			continue
		}
		if err := l.walkProblemDirs(childPath, childRelPath, visit); err != nil {
			return err
		}
	}
	return nil
}

func isProblemDir(entries []fs.DirEntry) bool {
	answerTargets := collectAnswerFileTargets(entries, nil)
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		if _, ok := answerTargets[name]; ok {
			continue
		}
		switch {
		case name == "metadata.yaml" || name == "description.md":
			return true
		case name == "validator.cpp" || name == "checker.cpp":
			return true
		case IsRoleFile(name, "correct"), IsRoleFile(name, "rejected"), IsRoleFile(name, "generator"), IsRoleFile(name, "singlegen"):
			return true
		case isTestcaseFile(name):
			return true
		}
	}
	return false
}

// IsProblemDir reports whether dirPath contains a recognized problem marker.
func IsProblemDir(dirPath string) (bool, error) {
	entries, err := os.ReadDir(dirPath)
	if err != nil {
		return false, err
	}
	return isProblemDir(entries), nil
}

func (l problemLoader) loadProblem(dirPath string, options Options) (Problem, error) {
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
	if data, err := l.files.ReadFile(metadataPath); err == nil {
		decoder := yaml.NewDecoder(bytes.NewReader(data))
		decoder.KnownFields(true)
		if err := decoder.Decode(&meta); err != nil {
			return Problem{}, fmt.Errorf("parse metadata: %w", err)
		}
	} else if !errors.Is(err, fs.ErrNotExist) {
		return Problem{}, err
	}
	if meta.Codes == nil {
		meta.Codes = map[string]string{}
	}

	descriptionBytes, err := l.files.ReadFile(filepath.Join(dirPath, "description.md"))
	description := ""
	if err == nil {
		description = string(descriptionBytes)
	} else if !errors.Is(err, fs.ErrNotExist) {
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
		OutputOnly:     meta.OutputOnly,
	}

	seen := map[string]struct{}{}
	entries, err := l.files.ReadDir(dirPath)
	if err != nil {
		return Problem{}, err
	}
	answerTargets := collectAnswerFileTargets(entries, meta.Codes)
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		seen[name] = struct{}{}
		classified := classifyProblemFile(name, answerTargets)
		if classified.Role == fileRoleMetadata || classified.Role == fileRoleDescription {
			continue
		}
		if ignoredRole, ok := outputOnlyIgnoredRole(classified.Role); problem.OutputOnly && ok {
			problem.IgnoredOutputOnlyFiles = append(problem.IgnoredOutputOnlyFiles, IgnoredOutputOnlyFile{
				Filename: name,
				Role:     ignoredRole,
			})
			continue
		}
		contentBytes, err := l.files.ReadFile(filepath.Join(dirPath, name))
		if err != nil {
			return Problem{}, err
		}
		authorName := sourceAuthor(name, meta.Authors, options.AuthorByRelPath, problemType, externalID)
		if classified.Role == fileRoleAnswer {
			problem.AnswerFiles = append(problem.AnswerFiles, AnswerFile{
				Filename:               name,
				Content:                string(contentBytes),
				AuthorName:             authorName,
				TargetProviderFilename: classified.TargetProviderFilename,
			})
			continue
		}
		switch classified.Role {
		case fileRoleValidator:
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Validator = &file
		case fileRoleChecker:
			file := CodeFile{Filename: name, Language: contracts.LanguageCpp23, Content: string(contentBytes), AuthorName: authorName}
			problem.Checker = &file
		case fileRoleCorrect:
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.CorrectCodes = append(problem.CorrectCodes, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case fileRoleRejected:
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.RejectedCodes = append(problem.RejectedCodes, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case fileRoleGenerator:
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Generators = append(problem.Generators, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case fileRoleSinglegen:
			lang, err := InferLanguage(name, meta.Codes)
			if err != nil {
				return Problem{}, err
			}
			problem.Singlegens = append(problem.Singlegens, CodeFile{Filename: name, Language: lang, Content: string(contentBytes), AuthorName: authorName})
		case fileRoleTestcase:
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
	slices.SortFunc(problem.RejectedCodes, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Generators, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Singlegens, func(a, b CodeFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.Testcases, func(a, b TestcaseFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.AnswerFiles, func(a, b AnswerFile) int { return strings.Compare(a.Filename, b.Filename) })
	slices.SortFunc(problem.IgnoredOutputOnlyFiles, func(a, b IgnoredOutputOnlyFile) int {
		return strings.Compare(a.Filename, b.Filename)
	})
	slices.Sort(problem.UnknownFiles)
	problem.Runnable = isRunnableProblem(problem)
	return problem, nil
}

func isRunnableProblem(problem Problem) bool {
	hasCorrect := len(problem.CorrectCodes) > 0
	hasProvider := len(problem.Generators)+len(problem.Singlegens)+len(problem.Testcases) > 0
	hasRequiredChecker := !problem.IsSpecialJudge || problem.Checker != nil
	if problem.OutputOnly {
		return hasCorrect && hasRequiredChecker
	}
	return hasCorrect && hasProvider && hasRequiredChecker
}

type fileRole string

const (
	fileRoleMetadata    fileRole = "metadata"
	fileRoleDescription fileRole = "description"
	fileRoleAnswer      fileRole = "answer"
	fileRoleValidator   fileRole = "validator"
	fileRoleChecker     fileRole = "checker"
	fileRoleCorrect     fileRole = "correct"
	fileRoleRejected    fileRole = "rejected"
	fileRoleGenerator   fileRole = "generator"
	fileRoleSinglegen   fileRole = "singlegen"
	fileRoleTestcase    fileRole = "testcase"
	fileRoleUnknown     fileRole = "unknown"
)

type classifiedProblemFile struct {
	Role                   fileRole
	TargetProviderFilename string
}

func classifyProblemFile(name string, answerTargets map[string]string) classifiedProblemFile {
	if name == "metadata.yaml" {
		return classifiedProblemFile{Role: fileRoleMetadata}
	}
	if name == "description.md" {
		return classifiedProblemFile{Role: fileRoleDescription}
	}
	if target, ok := answerTargets[name]; ok {
		return classifiedProblemFile{Role: fileRoleAnswer, TargetProviderFilename: target}
	}
	switch {
	case name == "validator.cpp":
		return classifiedProblemFile{Role: fileRoleValidator}
	case name == "checker.cpp":
		return classifiedProblemFile{Role: fileRoleChecker}
	case IsRoleFile(name, "correct"):
		return classifiedProblemFile{Role: fileRoleCorrect}
	case IsRoleFile(name, "rejected"):
		return classifiedProblemFile{Role: fileRoleRejected}
	case IsRoleFile(name, "generator"):
		return classifiedProblemFile{Role: fileRoleGenerator}
	case IsRoleFile(name, "singlegen"):
		return classifiedProblemFile{Role: fileRoleSinglegen}
	case isTestcaseFile(name):
		return classifiedProblemFile{Role: fileRoleTestcase}
	default:
		return classifiedProblemFile{Role: fileRoleUnknown}
	}
}

func outputOnlyIgnoredRole(role fileRole) (string, bool) {
	switch role {
	case fileRoleValidator, fileRoleAnswer, fileRoleGenerator, fileRoleSinglegen, fileRoleTestcase:
		return string(role), true
	default:
		return "", false
	}
}

func sourceAuthor(filename string, authors map[string]string, authorByRelPath map[string]string, problemType, externalID string) string {
	logicalPath := filepath.ToSlash(filepath.Join(problemType, externalID, filename))
	if author, ok := authorByRelPath[logicalPath]; ok {
		return author
	}
	return authors[filename]
}

func IsRoleFile(filename, role string) bool {
	base := strings.TrimSuffix(filepath.Base(filename), filepath.Ext(filename))
	return base == role || strings.HasPrefix(base, role+"_")
}

func isTestcaseFile(filename string) bool {
	base := filepath.Base(filename)
	return strings.HasPrefix(base, "testcase") || strings.Contains(base, ".in")
}

func collectAnswerFileTargets(entries []fs.DirEntry, overrides map[string]string) map[string]string {
	names := map[string]struct{}{}
	for _, entry := range entries {
		if !entry.IsDir() {
			names[entry.Name()] = struct{}{}
		}
	}

	answerTargets := map[string]string{}
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		if answerName, ok := testcaseAnswerFilename(name); ok {
			if _, exists := names[answerName]; exists {
				answerTargets[answerName] = name
			}
		}
		if isSinglegenSourceFile(name, overrides) {
			answerName := name + ".out"
			if _, exists := names[answerName]; exists {
				answerTargets[answerName] = name
			}
		}
	}
	return answerTargets
}

func testcaseAnswerFilename(filename string) (string, bool) {
	if !strings.Contains(filename, ".in") {
		return "", false
	}
	return strings.Replace(filename, ".in", ".out", 1), true
}

func isSinglegenSourceFile(filename string, overrides map[string]string) bool {
	if !IsRoleFile(filename, "singlegen") {
		return false
	}
	_, err := InferLanguage(filename, overrides)
	return err == nil
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
