---
name: create-validator
description: Create a testcase.ac competitive-programming input validator for an explicit problem directory= and problem description= prompt, using testlib.h, strict formatting, implied global constraints, and smoke tests against sample or generated example inputs.
metadata:
  short-description: Write and test testlib validators
---

# Create Validator

Use this skill when the user asks for `$create-validator` or wants a `validator.cpp` for a testcase.ac problem.

## Expected Input

- `problem directory=`: required when writing into this repository, for example `testcase/boj/1000`. If the user gives `testcase/.../metadata.yaml`, use its parent directory.
- `problem description=`: required unless the problem statement is already available in files or conversation context.
- sample inputs: optional; use statement samples when present.

If `problem directory=` is missing and there is no unambiguous target file already open in the user request, ask for it before editing.

## Workflow

1. Use the explicit `problem directory=` as the target directory, normalizing a `metadata.yaml` path to its parent directory.
2. Read the problem statement and any existing files in that directory, then extract:
   - input format, all numeric/string bounds, and whether multiple test cases exist;
   - explicit guarantees such as connected graph, valid simulation state, answer exists, answer bounded, non-degenerate geometry;
   - sample inputs, if present.
3. If `problem description=` is a PDF URL, extract the PDF to `tmp/pdfs/`, use text extraction plus page rendering when layout is ambiguous, and remove temporary PDF artifacts before finishing.
4. Save official statement samples as fixed testcase providers named `testcase_sample_1.txt`, `testcase_sample_2.txt`, etc. Preserve exact input formatting with a final newline.
5. Write `validator.cpp` in `problem directory=` using `testlib.h`.
6. Test it:
   - If official sample inputs exist, run the validator on the saved `testcase_sample_*.txt` files.
   - If no official sample inputs exist, create 2-3 small valid inputs from the statement, save them as temporary repo-local files, run the validator on them, then remove only those temporary files.
   - If the problem directory has generators or correct solutions, also run the full verifier:
     `./tests/verify/run_problems.sh testcase/<type>/<id>`.

## Validator Rules

- Validate from the input-validator perspective, not the solution perspective.
  - Do validate statement assumptions, such as graph connectivity if the statement says the graph is connected.
  - Do not validate the answer predicate itself when that is what contestants must determine.
- Validate every stated constraint and every input guarantee that a correct solution may rely on.
- Validate holistic properties by computing or simulating them when needed: connectivity, acyclicity, non-degenerate polygons, invariant-preserving simulations, feasibility/existence guarantees, and answer upper bounds stated as input promises.
- Be whitespace-strict. Use `readSpace()`, `readEoln()`, and finish with `readEof()`.
- Every read should have a descriptive name where testlib supports it.
- If the statement says a token is a number, enforce canonical numeric form. `readInt`, `readLong`, and related numeric readers already handle ordinary decimal integers. For huge/base-B/special numbers read as tokens, manually reject invalid leading zeroes, invalid signs, and out-of-alphabet digits. Do not enforce numeric canonical form for strings of digits or binary strings unless the statement says they are numbers.
- If the statement does not specify a maximum number of test cases, assume up to `100000`.
- Use `long long` or `__int128_t` for validator-side computations that can overflow smaller types.
- Use clear `ensuref` messages that include the failing index/value.

## Testlib Patterns

```cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    set<pair<int,int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();
        ensuref(a != b, "loop at edge %d: %d %d", i + 1, a, b);
        ensuref(edges.insert({min(a, b), max(a, b)}).second,
                "duplicate edge at edge %d: %d %d", i + 1, a, b);
    }

    inf.readEof();
}
```

Prefer `readInts` / `readLongs` for a whole line of same-bounded values, then call `readEoln()`.

For arbitrary string tokens, use `inf.readToken("[^]+", "name")`; a single argument to `readToken` is a regex, not a field name.

## Testing Commands

For quick sample validation inside the stresser Docker runtime:

```bash
.agents/skills/create-validator/scripts/check-validator.sh testcase/<type>/<id> sample1.txt sample2.txt
```

If no sample files are passed, the script uses existing `testcase_*.txt` files from the problem directory.

For full repository verification, including generator runs and validator checks:

```bash
./tests/verify/run_problems.sh testcase/<type>/<id>
```

The full verifier builds from `deploy/stresser.Dockerfile`, compiles helper code, runs generators for 100 seeds, and sends sampled cases through `validator.cpp` when present.

## Local Stresser Lambda

Use the local Lambda runtime only when an end-to-end stress invocation is needed:

```bash
docker build -f deploy/stresser.Dockerfile -t testcase-ac-stresser .
docker run --rm -p 9000:8080 testcase-ac-stresser
```

Invoke it with a `backend/contracts.StressEvent` JSON payload at:

```bash
curl -sS -X POST \
  http://localhost:9000/2015-03-31/functions/function/invocations \
  -H 'content-type: application/json' \
  --data @event.json
```

For validator-only work, prefer `check-validator.sh` and `tests/verify/run_problems.sh` because Lambda stress events do not execute standalone validators.
