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

Treat `ans` as the baseline claim. A checker should parse and validate each output stream, normalize it into a comparable claim, then compare participant `ouf` against jury `ans` under the statement's exact, tolerance, feasibility, or objective rule.

Use input-derived computation only to validate a supplied output object or compute the objective value of that supplied output. Do not compute an independent expected answer from input just to judge ordinary exact, scalar, floating, or effectively unique outputs.

- For a certificate, witness, path, subset, coordinate among ties, or any other non-unique object, use the shared parser pattern below. Validate both `ans` and `ouf` through that parser, even when `ouf` can be judged without comparing directly to `ans`.
- For exact or effectively unique output under legacy special-judge metadata, parse and validate the output format, then compare `ouf` to `ans`.
- For optimization output with a certificate or witness, validate both `ans` and `ouf` with the same parser, compute each output's objective from the supplied certificate, and compare objectives. If the participant output is semantically valid and strictly better than the jury output, return `_fail`.
- For value-only optimization output, treat the jury value in `ans` as the baseline. Parse and validate both scalar values, then compare participant objective against jury objective. Do not run a solver inside the checker to prove the jury value is globally optimal.
- Never read wall-clock time, random state, files, network, or other environment state to recreate an expected answer.

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

For optimization problems, compare participant output against jury output instead of solving the whole optimization problem inside the checker. Validate each supplied certificate or witness and compute its objective value when that value is derivable from the output and input. For value-only output, compare the scalar objective directly; reject impossible or malformed scalar values only when that is a direct output-validity check, not by running a full solver to certify that `ans` is globally optimal.

## Floating Tolerance

For floating-output problems, compare participant output to jury output using the statement's tolerance. The jury output is expected to be produced with sufficient precision for judging.

This applies to high-precision decimal and rational-style scalar outputs too. Parse `ans` and `ouf` with enough precision for the statement tolerance, then compare the participant value to the jury value.

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
- For negative/impossible sentinels such as `NO` or `-1`, parse the jury sentinel without trying to prove impossibility from the input. Do not independently prove impossibility inside the checker. If jury says impossible and participant supplies a witness, validate that witness; return `_fail` if it is valid, otherwise reject the participant output. If the statement requires an explicit impossibility certificate, validate that certificate as ordinary output data.
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
