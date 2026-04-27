---
name: create-generator
description: Create a testcase.ac C++ testlib generator for an explicit problem directory= and problem description= prompt, with small diverse hyperparameters, 100-run smoke testing, and optional validation through validator.cpp.
metadata:
  short-description: Write and test testcase generators
---

# Create Generator

Use this skill when the user asks for `$create-generator` or wants a testcase.ac `generator_*.cpp`.

## Expected Input

- `problem directory=`: required when writing into this repository, for example `testcase/boj/1000`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description=`: required unless the problem statement is already available in files or conversation context.
- generator filename: optional; choose the next local `generator_*.cpp` name if omitted and the directory pattern is clear.

If `problem directory=` is missing and there is no unambiguous target file already open in the user request, ask for it before editing.

## Workflow

1. Use the explicit `problem directory=` as the target directory, normalizing a `metadata.yaml` path to its parent directory.
2. Read the problem statement, existing `validator.cpp`, `correct_*`, fixed `testcase_*.txt`, and any current generators in that directory if available.
3. If `problem description=` is a PDF URL, extract it under `tmp/pdfs/`, use text extraction plus page rendering when layout is ambiguous, and remove temporary PDF artifacts before finishing.
4. If the statement has official sample inputs and they are not yet saved, add them as `testcase_sample_1.txt`, `testcase_sample_2.txt`, etc.
5. Write a single C++ generator using `testlib.h` in `problem directory=`.
6. Keep generated inputs valid, compact, and varied.
7. Test it:
   - Run the generator for 100 seeds.
   - Confirm every run exits successfully and emits a testcase.
   - If `validator.cpp` exists, validate all 100 generated cases.
   - Prefer the repo verifier for final confirmation:
     `./tests/verify/run_problems.sh testcase/<type>/<id>`.

## Generator Rules

- The first executable statement in `main` must be `registerGen(argc, argv, 1);`.
- Include every header you use.
- Print with `println(...)` where practical so spaces and newlines are correct.
- Use `rnd` for randomness:
  - `rnd.next(lo, hi)` for inclusive integer ranges;
  - `rnd.next(hi)` for `[0, hi)`;
  - `rnd.next()` for a double in `[0, 1)`;
  - `rnd.wnext(hi, t)` to bias toward high values when `t > 0` and low values when `t < 0`;
  - `rnd.any(container)` for random elements.
- Use `shuffle(v.begin(), v.end())` from `testlib.h`.
- Keep cases hand-checkable. As a default, graph `n` should often be `< 15`, strings often `< 30`, and outputs should usually stay under 500 characters unless the problem needs a larger case.
- Create multiple hyperparameters that expose different failure modes: size, density, value range, duplication rate, ordering, degeneracy/non-degeneracy mode, component shape, alphabet size, edge-case switches.
- Never rely on rejection sampling that can loop for a long time. Bound attempts and construct valid objects directly when possible.
- If a validator exists, treat validator rejection as a generator bug unless the validator is clearly wrong.

## Starter Shape

```cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int maxEdges = n * (n - 1) / 2;
    int m = rnd.next(0, maxEdges);

    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            edges.push_back({i, j});
        }
    }
    shuffle(edges.begin(), edges.end());
    edges.resize(m);

    println(n, m);
    for (auto [a, b] : edges) println(a, b);
}
```

Adapt the shape to the problem; do not generate graph input for non-graph problems.

## Testing Commands

Quick 100-seed check inside the stresser Docker runtime:

```bash
.agents/skills/create-generator/scripts/check-generator.sh testcase/<type>/<id> generator_name.cpp 100
```

The generator filename may be omitted if the problem directory has exactly one `generator*.cpp` candidate. If `validator.cpp` exists, the script compiles it and validates all generated cases.

Full repository verification:

```bash
./tests/verify/run_problems.sh testcase/<type>/<id>
```

The full verifier builds from `deploy/stresser.Dockerfile`, compiles sources, runs each generator for `100` seeds, validates generated cases when `validator.cpp` exists, and checks correct-solution consistency when `correct_*` files exist.

## Local Stresser Lambda

Use the local Lambda runtime for end-to-end stress behavior:

```bash
docker build -f deploy/stresser.Dockerfile -t testcase-ac-stresser .
docker run --rm -p 9000:8080 testcase-ac-stresser
```

Invoke it with a `backend/contracts.StressEvent` payload. A minimal shape is:

```json
{
  "operation": "stress",
  "requestId": "local-generator-check",
  "targetCode": "...wrong or candidate solution...",
  "targetCodeLang": "cpp23",
  "correctCode": "...reference solution...",
  "correctCodeLang": "cpp23",
  "targetTimeLimit": 2,
  "targetMemoryLimit": 256,
  "correctTimeLimit": 2,
  "correctMemoryLimit": 256,
  "iterations": 100,
  "caseProviders": [
    {
      "type": "generator",
      "id": "generator_local.cpp",
      "code": "...generator source...",
      "language": "cpp23"
    }
  ]
}
```

Then:

```bash
curl -sS -X POST \
  http://localhost:9000/2015-03-31/functions/function/invocations \
  -H 'content-type: application/json' \
  --data @event.json
```

For generator-only validation, prefer `check-generator.sh` and `tests/verify/run_problems.sh`; they test the generator directly and include validator integration.
