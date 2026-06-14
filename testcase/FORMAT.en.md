# Problem Data Format

[한국어](FORMAT.md) | English

A problem is a directory at `testcase/<problemType>/<externalId>/`. The
`problemType` namespace is open; whatever contributors add is what exists.

## Files

All files in a problem directory are optional, but a runnable/stressable problem
needs at least one `correct_*` solution. To allow an actual stress run, the
problem also needs at least one `generator_*`, `singlegen_*`, or fixed input
testcase, unless it is marked `outputOnly: true`.

### `metadata.yaml` (optional)

```yaml
title: "A+B"
externalLink: "https://www.acmicpc.net/problem/1000"
authors:                  # optional per-file author/source overrides
  correct_reference.cpp: "problem source or reference-code author"
  sample_1.in: "problem source"
timeLimitMs: 2000
memoryLimitMb: 256
isSpecialJudge: false
codes:                    # optional per-file language overrides
  correct_legacy.cpp: cpp14
```

- `title`: human-readable problem title.
- `externalLink`: URL of the original problem statement, if any.
- `authors`: optional map from filename to author or source. When set, this is
  displayed instead of the git commit author for that file only. Use it only
  for files that need explicit attribution, such as official reference code or
  sample inputs imported from an external contest or institution.
- `timeLimitMs`: per-testcase time limit in milliseconds.
- `memoryLimitMb`: per-testcase memory limit in megabytes.
- `isSpecialJudge`: whether the original problem is special-judged. This is
  used by the frontend to decide whether checker-related UI should be shown.
- `outputOnly`: set to `true` only for problems with no input. These problems
  use one implicit empty-stdin case, so do not add validators, generators,
  fixed testcases, or answer files.
- `codes`: optional map from source filename to a language tag that overrides
  extension-based inference, such as pinning a `.cpp` file to `cpp14` instead
  of the default `cpp23`.

### `type_metadata.yaml` (optional at problem-type directory)

`testcase/<problemType>/type_metadata.yaml` defines frontend browsing labels
and ordering for that problem type. Problem existence still comes from problem
directories in the filesystem; this file is display metadata.

Example: [koi/type_metadata.yaml](koi/type_metadata.yaml)

```yaml
schemaVersion: 1
label: KOI
segments:
  - label: "{}년"
  - label: "{}차대회"
  - labels:
      elem: "초등부"
      mid: "중등부"
      high: "고등부"
  - label: "{}번"
```

- `schemaVersion`: only `1` is currently supported.
- `label`: root problem-type label, such as showing `KOI` for `/koi`.
- `segments`: display rules for each depth after splitting `externalId` on
  `/`.
- `segments[].label`: display template. `{}` is replaced with the raw path
  segment.
- `segments[].labels`: maps specific path segments to display labels. The YAML
  order is also used as the frontend sort order. Without this, numeric-looking
  values sort numerically and other values sort lexicographically.

### `description.md` (optional)

Problem statement in Markdown. Omit this when you do not hold the copyright
to the original statement, such as third-party problems mirrored from external
judges.

### Reference Solution Code (`correct_*`) (required)

Reference solution. The filename must start with `correct` to be loaded as a
reference solution. Examples: `correct_basic.cpp`, `correct.py`. Language is
inferred from the extension unless overridden by `metadata.yaml`.

When multiple `correct_*` files exist, all are shown to users and one can be
selected for a stress request. The default order is lexicographic by filename.

### Generator Code (`generator_*`) (optional)

Random test generator. A file is loaded as a generator when its filename starts
with `generator`. Example: `generator_random.cpp`. The executable must accept
the seed as its first command-line argument and produce the same output for the
same seed. Generators using `testlib.h` automatically receive the seed as the
first command-line argument.

### Single Generator Code (`singlegen_*`) (optional)

Generator that produces fixed output. Use it when the output is too large to
commit as text. A file is loaded as a single generator when its filename starts
with `singlegen`. Example: `singlegen_large.py`.

### Fixed Testcases (`testcase_*` / `.in`) (optional)

Plaintext fixed testcases. A file is recognized as a fixed testcase when:

- The filename starts with `testcase`, for example `testcase_1.txt`.
- The filename contains `.in`, for example `sample.in` or `sample.in.txt`.

Statement samples should use `sample_{i}.in` and, when the official output is
available, `sample_{i}.out`.

Fixed testcases must be at most 8 KiB (8192 bytes). Add larger inputs as
`generator_*` or `singlegen_*` files.

### Fixed Answer Files (optional)

For single generator code and fixed testcases, you can provide the expected
output for that input as a fixed answer file.

For single generator code and fixed testcases, the matching fixed answer file
is selected by these rules:

- `.in` fixed testcase: if a file with the first `.in` replaced by `.out`
  exists, it is recognized as the fixed answer file. Example:
  `testcase_1.in.txt` -> `testcase_1.out.txt`.
- `singlegen_*`: if a file with `.out` appended to the filename exists, it is
  recognized as the fixed answer file. Example:
  `singlegen_1.py` -> `singlegen_1.py.out`.

Verification checks that reference solution output matches the answer file.
When `checker.cpp` exists, verification uses the checker. Otherwise it uses the
default output comparison.

### `validator.cpp` (required except output-only)

Input validator using `testlib.h`. Exactly this filename. Every committed
testcase provider output must pass this validator.

### `checker.cpp` (optional)

Special-judge checker using `testlib.h`. Exactly this filename. When present,
the stresser uses it to decide whether a submitted solution's output is
acceptable. When absent, the default output comparison is used; ordinary
accepted-output formatting should be enough.

## Supported Languages

These are the language tags accepted by the API/stresser:

- `cpp23`
- `cpp20`
- `cpp17`
- `cpp14`
- `c11`
- `c99`
- `python3`
- `pypy3`
- `java`
- `nodejs`
- `golang`
- `kotlin`
- `rust2021`
- `csharp`

Repository files infer these default tags by extension:

| Extension | Default tag |
|-----------|-------------|
| `.cpp`    | `cpp23`     |
| `.c`      | `c11`       |
| `.py`     | `python3`   |
| `.java`   | `java`      |
| `.js`     | `nodejs`    |
| `.go`     | `golang`    |
| `.kt`     | `kotlin`    |
| `.rs`     | `rust2021`  |
| `.cs`     | `csharp`    |

Use `metadata.yaml`'s `codes` map to pin a specific language tag per file.

## Determinism

Generators should be deterministic: running a generator twice with the same
seed should produce byte-identical output. Avoid `time(NULL)`,
`std::random_device`, and other non-reproducible sources.
