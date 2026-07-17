package loader

import (
	"io/fs"
	"os"
	"path/filepath"
	"reflect"
	"slices"
	"sort"
	"testing"
	"testing/fstest"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func newFakeProblemLoader(files map[string]string) problemLoader {
	return problemLoader{
		files: newMapFilesystem(files),
	}
}

type mapFilesystem struct {
	fsys fstest.MapFS
}

func newMapFilesystem(files map[string]string) mapFilesystem {
	fsys := fstest.MapFS{}
	for path, content := range files {
		fsys[filepath.ToSlash(path)] = &fstest.MapFile{Data: []byte(content), Mode: 0o644}
	}
	return mapFilesystem{fsys: fsys}
}

func (m mapFilesystem) Stat(path string) (fs.FileInfo, error) {
	return fs.Stat(m.fsys, filepath.ToSlash(path))
}

func (m mapFilesystem) ReadDir(path string) ([]fs.DirEntry, error) {
	return fs.ReadDir(m.fsys, filepath.ToSlash(path))
}

func (m mapFilesystem) ReadFile(path string) ([]byte, error) {
	return fs.ReadFile(m.fsys, filepath.ToSlash(path))
}

type readTrackingFilesystem struct {
	base      filesystem
	readPath  map[string]bool
	forbidden map[string]bool
}

func newReadTrackingFilesystem(files map[string]string, forbidden []string) *readTrackingFilesystem {
	forbiddenByPath := map[string]bool{}
	for _, path := range forbidden {
		forbiddenByPath[filepath.ToSlash(path)] = true
	}
	return &readTrackingFilesystem{
		base:      newMapFilesystem(files),
		readPath:  map[string]bool{},
		forbidden: forbiddenByPath,
	}
}

func (f *readTrackingFilesystem) Stat(path string) (fs.FileInfo, error) {
	return f.base.Stat(path)
}

func (f *readTrackingFilesystem) ReadDir(path string) ([]fs.DirEntry, error) {
	return f.base.ReadDir(path)
}

func (f *readTrackingFilesystem) ReadFile(path string) ([]byte, error) {
	normalized := filepath.ToSlash(path)
	f.readPath[normalized] = true
	if f.forbidden[normalized] {
		return nil, fs.ErrPermission
	}
	return f.base.ReadFile(path)
}

func TestLoadProblemRejectsUnknownMetadataField(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"boj/1000/metadata.yaml": "title: A+B\nunknown: true\n",
	})

	if _, err := loader.loadProblem("boj/1000", Options{}); err == nil {
		t.Fatalf("LoadProblem() succeeded with unknown metadata field")
	}
}

func TestLoadProblemRejectsDirectoryWideAuthor(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"koi/2019/1/elem/1/metadata.yaml": "title: A+B\nauthor: 한국정보올림피아드\n",
	})

	if _, err := loader.loadProblem("koi/2019/1/elem/1", Options{}); err == nil {
		t.Fatalf("LoadProblem() succeeded with directory-wide author")
	}
}

func TestLoadProblemAuthorIndexTakesPrecedenceWithMetadataFallback(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"koi/2019/1/elem/1/metadata.yaml":         "title: A+B\nauthors:\n  correct_reference.cpp: logical-override\n  generator_1.cpp: metadata-fallback\n",
		"koi/2019/1/elem/1/correct_reference.cpp": "int main(){}\n",
		"koi/2019/1/elem/1/generator_1.cpp":       "int main(){}\n",
	})

	problem, err := loader.loadProblem("koi/2019/1/elem/1", Options{
		ProblemType: "koi",
		ExternalID:  "2019/1/elem/1",
		AuthorByRelPath: map[string]string{
			"koi/2019/1/elem/1/correct_reference.cpp": "resolved-donor-author",
		},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(problem.CorrectCodes) != 1 {
		t.Fatalf("len(CorrectCodes) = %d, want 1", len(problem.CorrectCodes))
	}
	if got := problem.CorrectCodes[0].AuthorName; got != "resolved-donor-author" {
		t.Fatalf("CorrectCodes[0].AuthorName = %q, want resolved author index entry", got)
	}
	if len(problem.Generators) != 1 {
		t.Fatalf("len(Generators) = %d, want 1", len(problem.Generators))
	}
	if got := problem.Generators[0].AuthorName; got != "metadata-fallback" {
		t.Fatalf("Generators[0].AuthorName = %q, want metadata fallback", got)
	}
}

func TestBuildCatalogUsesInjectedFilesystemAndAuthorIndex(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"testcase/boj/1000/metadata.yaml":         "title: A+B\n",
		"testcase/boj/1000/correct.cpp":           "int main(){}\n",
		"testcase/boj/1000/testcase_1.txt":        "1 2\n",
		"testcase/boj/1001/rejected_wrong.cpp":    "int main(){}\n",
		"testcase/koi/2020/1/elem/1/title":        "ignored\n",
		"testcase/koi/2020/1/elem/1/README":       "ignored\n",
		"testcase/koi/2020/1/mid/2/metadata.yaml": "title: KOI\n",
	})

	catalog, err := loader.buildCatalog("testcase", map[string]string{
		"boj/1000/correct.cpp": "alice",
	})
	if err != nil {
		t.Fatal(err)
	}

	bojProblem, ok := catalog[[2]string{"boj", "1000"}]
	if !ok {
		t.Fatalf("catalog missing boj/1000: %+v", catalog)
	}
	if got := bojProblem.Title; got != "A+B" {
		t.Fatalf("boj/1000 title = %q, want A+B", got)
	}
	if got := bojProblem.CorrectCodes[0].AuthorName; got != "alice" {
		t.Fatalf("boj/1000 correct author = %q, want alice", got)
	}
	rejectedOnlyProblem, ok := catalog[[2]string{"boj", "1001"}]
	if !ok {
		t.Fatalf("catalog missing rejected-only boj/1001: %+v", catalog)
	}
	if got := rejectedOnlyProblem.RejectedCodes[0].Filename; got != "rejected_wrong.cpp" {
		t.Fatalf("boj/1001 rejected file = %q, want rejected_wrong.cpp", got)
	}
	if _, ok := catalog[[2]string{"koi", "2020/1/mid/2"}]; !ok {
		t.Fatalf("catalog missing nested koi problem: %+v", catalog)
	}
	if _, ok := catalog[[2]string{"koi", "2020/1/elem/1"}]; ok {
		t.Fatalf("catalog included non-problem directory: %+v", catalog)
	}
}

func TestBuildCatalogFindsNestedProblemsAndSymlinkDirs(t *testing.T) {
	dir := t.TempDir()
	testcaseRoot := filepath.Join(dir, "testcase")
	realProblemDir := filepath.Join(testcaseRoot, "koi", "2020", "1", "elem", "1")
	if err := os.MkdirAll(realProblemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(realProblemDir, "metadata.yaml"), []byte("title: Shared\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(realProblemDir, "correct_reference.cpp"), []byte("int main(){}\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	linkParent := filepath.Join(testcaseRoot, "koi", "2020", "1", "high")
	if err := os.MkdirAll(linkParent, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.Symlink(filepath.Join("..", "elem", "1"), filepath.Join(linkParent, "1")); err != nil {
		t.Fatal(err)
	}

	catalog, err := BuildCatalog(testcaseRoot, nil)
	if err != nil {
		t.Fatal(err)
	}
	gotIDs := make([]string, 0, len(catalog))
	for key := range catalog {
		if key[0] == "koi" {
			gotIDs = append(gotIDs, key[1])
		}
	}
	sort.Strings(gotIDs)
	wantIDs := []string{"2020/1/elem/1", "2020/1/high/1"}
	if len(gotIDs) != len(wantIDs) {
		t.Fatalf("koi ids = %v, want %v", gotIDs, wantIDs)
	}
	for i := range wantIDs {
		if gotIDs[i] != wantIDs[i] {
			t.Fatalf("koi ids = %v, want %v", gotIDs, wantIDs)
		}
	}
	if got := catalog[[2]string{"koi", "2020/1/high/1"}].Title; got != "Shared" {
		t.Fatalf("symlinked problem title = %q, want Shared", got)
	}
}

func TestIsProblemDir(t *testing.T) {
	dir := t.TempDir()
	if err := os.WriteFile(filepath.Join(dir, "validator.cpp"), nil, 0o644); err != nil {
		t.Fatal(err)
	}

	got, err := IsProblemDir(dir)
	if err != nil {
		t.Fatal(err)
	}
	if !got {
		t.Fatal("IsProblemDir() = false, want true")
	}

	if _, err := IsProblemDir(filepath.Join(dir, "missing")); err == nil {
		t.Fatal("IsProblemDir() succeeded for a missing directory")
	}
}

func TestLoadTypeMetadataPreservesOrderedLabels(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"koi/" + typeMetadataName: `schemaVersion: 1
label: KOI
segments:
  - label: "{}년"
  - label: "{}차대회"
  - labels:
      elem: "초등부"
      mid: "중등부"
      high: "고등부"
  - label: "{}번"
`,
	})

	metadata, err := loader.loadTypeMetadata("koi")
	if err != nil {
		t.Fatal(err)
	}
	if metadata == nil {
		t.Fatal("LoadTypeMetadata() = nil, want metadata")
	}
	if metadata.Label != "KOI" {
		t.Fatalf("Label = %q, want KOI", metadata.Label)
	}
	if got := metadata.Segments[0].Label; got != "{}년" {
		t.Fatalf("first segment label = %q, want {}년", got)
	}
	labels := metadata.Segments[2].Labels
	wantValues := []string{"elem", "mid", "high"}
	if len(labels) != len(wantValues) {
		t.Fatalf("labels = %#v, want %v", labels, wantValues)
	}
	for i, want := range wantValues {
		if labels[i].Value != want {
			t.Fatalf("label order = %#v, want %v", labels, wantValues)
		}
	}
}

func TestLoadProblemInfersAndSortsFiles(t *testing.T) {
	loader := newFakeProblemLoader(map[string]string{
		"boj/1000/metadata.yaml":       "title: A+B\ncodes:\n  correct_slow.cpp: cpp14\n",
		"boj/1000/correct.cpp":         "int main(){}",
		"boj/1000/correct_slow.cpp":    "int main(){}",
		"boj/1000/correct_fast.js":     "console.log(0)",
		"boj/1000/rejected.cpp":        "int main(){}",
		"boj/1000/rejected_slow.js":    "console.log(0)",
		"boj/1000/generator.py":        "print('1 2')",
		"boj/1000/generator_random.js": "console.log('1 2')",
		"boj/1000/singlegen.py":        "print('1 2')",
		"boj/1000/singlegen_edge.js":   "console.log('1 2')",
		"boj/1000/testcase.txt":        "1 2\n",
		"boj/1000/testcase_sample.txt": "1 2\n",
	})

	problem, err := loader.loadProblem("boj/1000", Options{})
	if err != nil {
		t.Fatal(err)
	}
	if got := problem.CorrectCodes[0].Filename; got != "correct.cpp" {
		t.Fatalf("first correct file = %q, want sorted correct.cpp", got)
	}
	if got := problem.CorrectCodes[2].Language; got != contracts.LanguageCpp14 {
		t.Fatalf("override language = %q, want cpp14", got)
	}
	if got := problem.RejectedCodes[0].Filename; got != "rejected.cpp" {
		t.Fatalf("first rejected file = %q, want sorted rejected.cpp", got)
	}
	if got := problem.RejectedCodes[0].Language; got != contracts.LanguageCpp23 {
		t.Fatalf("rejected language = %q, want cpp23", got)
	}
	if len(problem.CorrectCodes) != 3 || len(problem.RejectedCodes) != 2 || len(problem.Generators) != 2 || len(problem.Singlegens) != 2 || len(problem.Testcases) != 2 {
		t.Fatalf("loaded problem counts = correct:%d rejected:%d generator:%d singlegen:%d testcase:%d", len(problem.CorrectCodes), len(problem.RejectedCodes), len(problem.Generators), len(problem.Singlegens), len(problem.Testcases))
	}
	if !problem.Runnable {
		t.Fatal("Runnable = false, want true")
	}
}

func TestLoadProblemClassifiesAnswerFiles(t *testing.T) {
	// Given: a problem directory with testcase, .in, and singlegen answer naming patterns.
	loader := newFakeProblemLoader(map[string]string{
		"boj/1000/correct.cpp":           "int main(){}",
		"boj/1000/validator.cpp":         "int main(){}",
		"boj/1000/case.in.data":          "4 5\n",
		"boj/1000/case.out.data":         "9\n",
		"boj/1000/testcase_1.in.txt":     "1 2\n",
		"boj/1000/testcase_1.out.txt":    "3\n",
		"boj/1000/testcase_legacy.data":  "6 7\n",
		"boj/1000/singlegen_edge.py":     "print('6 7')",
		"boj/1000/singlegen_edge.py.out": "13\n",
	})

	// When: the loader classifies the problem files.
	problem, err := loader.loadProblem("boj/1000", Options{})
	if err != nil {
		t.Fatal(err)
	}

	// Then: input providers and answer files are separated with the expected provider links.
	gotTestcases := testcaseFilenames(problem.Testcases)
	wantTestcases := []string{"case.in.data", "testcase_1.in.txt", "testcase_legacy.data"}
	if !slices.Equal(gotTestcases, wantTestcases) {
		t.Fatalf("testcases = %v, want %v", gotTestcases, wantTestcases)
	}

	gotAnswers := map[string]string{}
	for _, answer := range problem.AnswerFiles {
		gotAnswers[answer.Filename] = answer.TargetProviderFilename
	}
	wantAnswers := map[string]string{
		"case.out.data":         "case.in.data",
		"singlegen_edge.py.out": "singlegen_edge.py",
		"testcase_1.out.txt":    "testcase_1.in.txt",
	}
	if !reflect.DeepEqual(gotAnswers, wantAnswers) {
		t.Fatalf("answers = %v, want %v", gotAnswers, wantAnswers)
	}
	if len(problem.UnknownFiles) != 0 {
		t.Fatalf("UnknownFiles = %v, want none", problem.UnknownFiles)
	}
}

func TestLoadProblemOutputOnlySuppressesInputMaterialsWithoutReadingContent(t *testing.T) {
	// Given: an output-only directory still containing old validator and provider files.
	files := map[string]string{
		"boj/1000/metadata.yaml":         "title: A+B\noutputOnly: true\ncodes:\n  generator_1.bad: python3\nauthors:\n  validator.cpp: alice\n",
		"boj/1000/correct.cpp":           "int main(){}",
		"boj/1000/checker.cpp":           "int main(){}",
		"boj/1000/validator.cpp":         "must not be read",
		"boj/1000/generator_1.bad":       "must not be read",
		"boj/1000/singlegen_edge.py":     "must not be read",
		"boj/1000/singlegen_edge.py.out": "must not be read",
		"boj/1000/testcase_1.in":         "must not be read",
		"boj/1000/testcase_1.out":        "must not be read",
	}
	forbidden := []string{
		"boj/1000/validator.cpp",
		"boj/1000/generator_1.bad",
		"boj/1000/singlegen_edge.py",
		"boj/1000/singlegen_edge.py.out",
		"boj/1000/testcase_1.in",
		"boj/1000/testcase_1.out",
	}
	tracker := newReadTrackingFilesystem(files, forbidden)
	loader := problemLoader{
		files: tracker,
	}

	// When: the loader builds the domain problem.
	problem, err := loader.loadProblem("boj/1000", Options{})
	if err != nil {
		t.Fatal(err)
	}

	// Then: forbidden files are excluded from usable materials and recorded by filename only.
	if !problem.OutputOnly {
		t.Fatal("OutputOnly = false, want true")
	}
	if problem.Validator != nil {
		t.Fatalf("Validator = %#v, want nil", problem.Validator)
	}
	if len(problem.Generators) != 0 || len(problem.Singlegens) != 0 || len(problem.Testcases) != 0 || len(problem.AnswerFiles) != 0 {
		t.Fatalf("usable input materials = generators:%d singlegens:%d testcases:%d answers:%d, want all zero", len(problem.Generators), len(problem.Singlegens), len(problem.Testcases), len(problem.AnswerFiles))
	}
	gotIgnored := ignoredOutputOnlyFilenames(problem.IgnoredOutputOnlyFiles)
	wantIgnored := []string{
		"generator_1.bad",
		"singlegen_edge.py",
		"singlegen_edge.py.out",
		"testcase_1.in",
		"testcase_1.out",
		"validator.cpp",
	}
	if !slices.Equal(gotIgnored, wantIgnored) {
		t.Fatalf("IgnoredOutputOnlyFiles = %v, want %v", gotIgnored, wantIgnored)
	}
	for _, path := range forbidden {
		if tracker.readPath[path] {
			t.Fatalf("ReadFile(%q) was called for suppressed output-only material", path)
		}
	}
}

func testcaseFilenames(files []TestcaseFile) []string {
	out := make([]string, 0, len(files))
	for _, file := range files {
		out = append(out, file.Filename)
	}
	return out
}

func ignoredOutputOnlyFilenames(files []IgnoredOutputOnlyFile) []string {
	out := make([]string, 0, len(files))
	for _, file := range files {
		out = append(out, file.Filename)
	}
	return out
}

func TestLoadProblemComputesRunnable(t *testing.T) {
	tests := []struct {
		name  string
		files map[string]string
		want  bool
	}{
		{
			name: "correct and generator",
			files: map[string]string{
				"correct.cpp":   "int main(){}",
				"generator.cpp": "int main(){}",
			},
			want: true,
		},
		{
			name: "correct and singlegen",
			files: map[string]string{
				"correct.cpp":  "int main(){}",
				"singlegen.py": "print('1 2')",
			},
			want: true,
		},
		{
			name: "correct and testcase",
			files: map[string]string{
				"correct.cpp":         "int main(){}",
				"testcase_sample.txt": "1 2\n",
			},
			want: true,
		},
		{
			name: "correct without provider",
			files: map[string]string{
				"correct.cpp": "int main(){}",
			},
			want: false,
		},
		{
			name: "rejected with provider but no correct",
			files: map[string]string{
				"rejected.cpp":  "int main(){}",
				"generator.cpp": "int main(){}",
			},
			want: false,
		},
		{
			name: "generator without correct",
			files: map[string]string{
				"generator.cpp": "int main(){}",
			},
			want: false,
		},
		{
			name: "special judge without checker",
			files: map[string]string{
				"metadata.yaml": "isSpecialJudge: true\n",
				"correct.cpp":   "int main(){}",
				"generator.cpp": "int main(){}",
			},
			want: false,
		},
		{
			name: "special judge with checker",
			files: map[string]string{
				"metadata.yaml": "isSpecialJudge: true\n",
				"correct.cpp":   "int main(){}",
				"generator.cpp": "int main(){}",
				"checker.cpp":   "int main(){}",
			},
			want: true,
		},
		{
			name: "output only with correct and no provider",
			files: map[string]string{
				"metadata.yaml": "outputOnly: true\n",
				"correct.cpp":   "int main(){}",
			},
			want: true,
		},
		{
			name: "output only special judge with checker and no provider",
			files: map[string]string{
				"metadata.yaml":   "outputOnly: true\nisSpecialJudge: true\n",
				"correct.cpp":     "int main(){}",
				"checker.cpp":     "int main(){}",
				"testcase_old.in": "1\n",
			},
			want: true,
		},
		{
			name: "output only special judge without checker",
			files: map[string]string{
				"metadata.yaml": "outputOnly: true\nisSpecialJudge: true\n",
				"correct.cpp":   "int main(){}",
			},
			want: false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			files := map[string]string{}
			for name, content := range tt.files {
				files[filepath.Join("boj", "1000", name)] = content
			}
			loader := newFakeProblemLoader(files)

			problem, err := loader.loadProblem("boj/1000", Options{})
			if err != nil {
				t.Fatal(err)
			}
			if problem.Runnable != tt.want {
				t.Fatalf("Runnable = %v, want %v", problem.Runnable, tt.want)
			}
		})
	}
}
