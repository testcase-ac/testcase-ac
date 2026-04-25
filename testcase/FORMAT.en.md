# Problem Data Format

[한국어](FORMAT.md) | English

A problem is a directory at `testcase/<problemType>/<externalId>/`. The
`problemType` namespace is open; whatever contributors add is what exists.

## Files

All files in a problem directory are optional, but a runnable/stressable problem
needs at least one `correct_*` solution. To allow an actual stress run, the
problem also needs at least one `generator_*`, `singlegen_*`, or
`testcase_*.txt` file.

### `metadata.yaml` (optional)

```yaml
title: "A+B"
externalLink: "https://www.acmicpc.net/problem/1000"
timeLimitMs: 2000
memoryLimitMb: 256
isSpecialJudge: false
codes:                    # optional per-file language overrides
  correct_legacy.cpp: cpp14
```

- `title`: human-readable problem title.
- `externalLink`: URL of the original problem statement, if any.
- `timeLimitMs`: per-testcase time limit in milliseconds.
- `memoryLimitMb`: per-testcase memory limit in megabytes.
- `isSpecialJudge`: whether the original problem is special-judged. This is
  used by the frontend to decide whether checker-related UI should be shown.
- `codes`: optional map from source filename to a language tag that overrides
  extension-based inference, such as pinning a `.cpp` file to `cpp14` instead
  of the default `cpp23`.

### `description.md` (optional)

Problem statement in Markdown. Omit this when you do not hold the copyright
to the original statement, such as third-party problems mirrored from external
judges.

### `correct_*` (at least one required for a stressable problem)

Reference solution. The filename must start with `correct` to be loaded as a
reference solution. Examples: `correct_basic.cpp`, `correct.py`. Language is
inferred from the extension unless overridden by `metadata.yaml`.

When multiple `correct_*` files exist, all are shown to users and one can be
selected for a stress request. The default order is lexicographic by filename.

### `generator_*` (optional)

Parametric random test generator. The filename must start with `generator` to
be loaded as a generator. Example: `generator_random.cpp`. The resulting binary
must accept the seed as its first positional argument, and must produce
byte-identical output for the same seed.

### `singlegen_*` (optional)

One-off generator that produces a fixed output without reading a seed. Useful
when the output is too large to commit as plaintext but the generation logic
is deterministic. The filename must start with `singlegen` to be loaded as a
single-generator. Example: `singlegen_large.py`.

### `testcase_*.txt` (optional)

Plaintext fixed inputs. The filename must start with `testcase` and end with
`.txt` to be loaded as a fixed input. Example: `testcase_sample.txt`. Must be
valid UTF-8 text.

### `validator.cpp` (optional)

Input validator using `testlib.h`. Exactly this filename.

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
