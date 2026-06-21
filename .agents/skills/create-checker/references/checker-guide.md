# Checker Guide

Use this reference when designing testcase.ac `checker.cpp` files and targeted checker cases.

## Checker Boundary

A checker validates contestant output for one input and compares it with jury output when needed. It is not an input validator, generator, or replacement for the reference solution.

Do not add a checker only to reimplement exact output comparison.

## Source Of Truth

Build the output contract from these sources, in this order:

1. The provided problem statement, including output format, tolerance, optimality, and certificate rules.
2. Official samples and answer files as examples.
3. Existing correct solutions as jury-output producers.
4. A local choice when the statement is ambiguous or contradictory.

Correct solutions and answer files can expose conflicts, but they do not override the statement.

## testlib Basics

Use `registerTestlibCmd(argc, argv)` and the three testlib streams:

- `inf`: input file;
- `ouf`: participant output;
- `ans`: jury answer.

Use `quitf(_ok, ...)` for accepted output and `quitf(_wa, ...)` for wrong participant output. Use `_fail` when jury output is invalid, the checker reaches an impossible internal state, or the participant output is strictly better than the jury output in an optimization problem.

Prefer bounded reads with names for participant-controlled data:

```cpp
int k = ouf.readInt(0, n, "answer length");
int v = ouf.readInt(1, n, format("answer[%d]", i + 1).c_str());
```

## Jury Baseline

Treat `ans` as the judging baseline. Add checker logic only for the non-exact rule that made a checker necessary.

- For a certificate, witness, path, subset, coordinate among ties, or any other non-unique object, use the shared parser pattern below. Use `inf` to validate the submitted object and compute the object's claimed value when needed.
- Do not turn a checker into a second full reference solution for ordinary unique-output problems.
- If the participant output is semantically valid and strictly better than the jury output for an optimization problem, return `_fail`.

## Shared Answer Parser

By default, parse jury and participant output through the same function. This keeps participant and jury validation identical. Use `stream.quitf(_wa, ...)` so invalid `ouf` is wrong answer and invalid `ans` is checker failure.

`readAns` should parse and validate one output stream, then return a normalized or comparable answer. It should not decide whether the participant beats, matches, or loses to jury output. Do that comparison in `main` after reading both streams.

```cpp
#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

int n, m, s, t;
map<pair<int, int>, int> weight;

struct Answer {
    long long value;
};

Answer readAns(InStream& stream) {
    int len = stream.readInt(2, n, "path length");
    stream.readEoln();

    vector<int> path(len);
    vector<int> used(n + 1, 0);
    for (int i = 0; i < len; ++i) {
        path[i] = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
        if (used[path[i]]) {
            stream.quitf(_wa, "vertex %d is repeated", path[i]);
        }
        used[path[i]] = 1;
    }
    stream.readEoln();
    stream.readEof();

    if (path.front() != s) {
        stream.quitf(_wa, "path starts at %d instead of %d", path.front(), s);
    }
    if (path.back() != t) {
        stream.quitf(_wa, "path ends at %d instead of %d", path.back(), t);
    }

    long long value = 0;
    for (int i = 0; i + 1 < len; ++i) {
        auto it = weight.find({path[i], path[i + 1]});
        if (it == weight.end()) {
            stream.quitf(_wa, "edge (%d, %d) is not in the graph", path[i], path[i + 1]);
        }
        value += it->second;
    }
    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        weight[{u, v}] = weight[{v, u}] = w;
    }
    s = inf.readInt();
    t = inf.readInt();

    Answer jury = readAns(ans);
    Answer part = readAns(ouf);

    if (part.value < jury.value) {
        quitf(_wa, "jury has better answer: jury=%lld participant=%lld", jury.value, part.value);
    }
    if (part.value == jury.value) {
        quitf(_ok, "answer=%lld", part.value);
    }
    quitf(_fail, "participant found better answer: jury=%lld participant=%lld", jury.value, part.value);
}
```

For optimization problems, prefer comparing participant output against the jury output rather than solving the whole optimization problem inside the checker. The checker should still validate each output certificate and compute the value claimed by that output when the value is derivable from the certificate and input.

## Floating Tolerance

For floating-output problems, compare participant output to jury output using the statement's tolerance. The jury output is expected to be produced with sufficient precision for judging.

Use `doubleCompare` when the statement allows absolute-or-relative error. If the statement defines only absolute error, only relative error, percentage error, or another custom tolerance, implement that rule directly.

This runnable example checks one floating value where the statement allows absolute or relative error at most `1e-2`:

```cpp
#include "testlib.h"
using namespace std;

const double EPS = 1e-2;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = ans.readDouble();
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    double part = ouf.readDouble();
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    if (!doubleCompare(jury, part, EPS)) {
        quitf(_wa,
              "expected %.10f, found %.10f, error %.10f",
              jury, part, doubleDelta(jury, part));
    }
    quitf(_ok, "answer %.10f is within tolerance", part);
}
```

## Output Rules

- Validate the participant output format before semantic checks.
- Guard every index before indexing vectors or arrays.
- Reject extra participant output unless the statement allows it.
- When enforcing EOF after a line-based output token, consume the expected end-of-line before `readEof()`.
- Validate the jury answer when it contains a certificate, claimed optimum, or feasibility decision that can be checked.
- For `NO` or `YES` plus witness, if jury says impossible but participant provides a valid witness, return `_fail`.
- Follow the statement's output format, including line structure when the statement specifies it. Use token-flexible parsing only when line layout is not part of the contract.
- Use `long long` or wider arithmetic for computed scores, sums, products, and path costs.
- Write diagnostic messages that include the failing field, index, and values.

## Targeted Cases

Before reporting success, run a few scratch cases against the checker. Keep these cases small and purpose-built; do not add them to the problem directory unless the user explicitly asks for persistent evidence.

Use expected verdicts:

- `accepted`: checker should return accepted.
- `rejected`: checker should reject participant output with wrong-answer or presentation-error.
- `wrong-answer`: checker should return wrong-answer specifically.
- `presentation-error`: checker should return presentation-error specifically.
- `fail`: checker should return checker failure.

Use `rejected` for most bad participant-output cases so the check is not fragile to whether testlib reports malformed output as wrong-answer or presentation-error.

For tolerance, tie, witness, or multiple-answer problems, include an accepted case where participant output differs from jury output but is still valid under the statement. For floating tolerance, include one value close to the tolerance boundary and one outside it. For tie or multiple-witness output, include a different valid tie/witness when a small case can provide one.

## Narrow Gate

Run:

```bash
.agents/skills/create-checker/scripts/check-checker-case.sh testcase/<type>/<id> <expected> <input-file> <participant-file> <jury-file>
```

This compiles `checker.cpp` in the same Docker runtime used by testcase.ac checks and runs one explicit `(input, participant output, jury output, expected verdict)` case. Repeat it for each targeted case.

Do not use full `./tests/verify/run_problems.sh testcase/<type>/<id>` as the checker completion criterion. Full verification is a broad integration pass that can fail for unrelated providers, validators, answer files, or correct solutions, and a permissive checker can still pass it.
