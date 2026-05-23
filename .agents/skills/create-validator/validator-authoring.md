# Validator Authoring

Use these rules when writing `validator.cpp` for testcase.ac problem data.

## Scope

- Validate from the input-validator perspective, not the solution perspective.
- Reject vacuous, undefined, or impractically huge inputs even when the
  statement forgot a boundary.
- Validate every stated input constraint and every stated input guarantee that a correct solution may rely on.
- Do validate statement assumptions such as connected graphs, valid simulation states, answer existence guarantees, bounded answers, and non-degenerate geometry.
- Do not validate the answer predicate itself when contestants are supposed to determine it.

## Formatting

- Be whitespace-strict. Use `readSpace()`, `readEoln()`, and finish with `readEof()`.
- Every read should have a descriptive name where testlib supports it.
- Prefer `readInts` and `readLongs` for a whole line of same-bounded values, then call `readEoln()`.
- For arbitrary string tokens, use `inf.readToken("[^]+", "name")`; a single argument to `readToken` is a regex, not a field name.
- Reject empty or whitespace-only input by default. For ordinary tokens or
  lines, require at least one non-whitespace character unless the statement
  explicitly allows an empty string, empty line, or whitespace-only line. A
  maximum length or allowed space character alone does not make the blank case
  valid. Allowing leading or trailing whitespace does not explicitly allow
  whitespace-only input.

## Numeric Values

- If the statement says a token is a number, enforce canonical numeric form.
- `readInt`, `readLong`, and related numeric readers already handle ordinary decimal integers.
- For huge integers, base-B numbers, or special numeric tokens read as strings, manually reject invalid leading zeroes, invalid signs, and out-of-alphabet digits.
- Do not enforce numeric canonical form for strings of digits or binary strings unless the statement says they are numbers.
- In xor/bitwise contexts, treat integer values as nonnegative unless the
  statement explicitly allows negatives.
- Use `long long` or `__int128_t` for validator-side computations that can overflow smaller types.

## Fixed-Size Relaxations

- If the statement fixes a large count or length only to set workload scale, the
  validator may accept smaller representative inputs down to `1` when the
  smaller size preserves the same input shape and solution logic.
  - Example 1: a multi-case problem fixes `T = 1000`, but each testcase is
    independent. In this case, allow `T` down to `1`.
  - Example 2: a bitwise-operation problem fixes the binary string length to
    `100000`, but shorter equal-length bit-vectors preserve the same input shape
    and solution logic. In this case, allow the length down to `1`.
- Do not use this relaxation generically. Use it only when a high lower bound or
  exact fixed size, at least `1000`, forces the smallest valid testcase to be so
  large that it is hard for users to read or inspect manually. If the high lower
  bound does not create a large testcase byte size, do not apply this
  relaxation.
- Do not use this relaxation for semantic scalar constants, value bounds,
  small-version constants, non-independent structures, or constraints that
  define the problem's case class. Those should follow the official statement
  exactly.

## Holistic Properties

Compute or simulate whole-input properties when the statement guarantees them:

- connectivity
- acyclicity
- uniqueness
- non-degenerate polygons or geometry
- valid state transitions
- feasibility or existence guarantees
- aggregate bounds such as total `N` over test cases

Use clear `ensuref` messages that include the failing index or value.

## Practical Size Bounds

- If an input-size count has no upper bound, add a practical cap from nearby
  constraints.
- Add a nearby `// CHECK` comment for practical caps that are not written in
  the statement.
- Example: if `N <= 1000`, cap graph edges at `1000000` because that matches
  the `N^2` scale.
- For primarily numeric input, reject inputs that force around `5000000` or
  more scalar tokens, unless the statement explicitly allows a larger input.
- For primarily string input, reject inputs around `10000000` or more
  characters, unless the statement explicitly allows a larger input.
- If the statement does not specify a maximum number of test cases, assume up to
  `100000`.

## Ambiguous Input Contracts

When the statement leaves one constraint unclear, identify the stricter
validator rule and the less restrictive rule it would replace. Choose between
those two rules by answering these questions in order.

1. Would accepting the broader case make the central problem object absent or
   contradict how it is defined? If yes, enforce the stricter rule.
   Example: if `N` is the size of a group, collection, or game instance, and
   the written bounds only say `N` is an integer below some upper limit, do not
   allow `N = 0` unless the statement explicitly allows an empty instance.
2. Otherwise, is the stricter rule explicitly stated, needed by a stated input
   guarantee, or needed to keep the input useful and well-defined? Unless so,
   use the less restrictive rule. Example: if the input gives positions of `N`
   marked points on a line but does not say the positions are distinct, accept
   two points with the same coordinate.

Whenever either choice depends on this ambiguity judgment, add a nearby comment
containing `// CHECK`. This includes common structural checks such as distinct
values, unique edges, no self-loops, positive weights, connectivity, or
feasibility, whether the validator enforces or omits the stricter rule.

## Pattern

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

    set<pair<int, int>> edges;
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
