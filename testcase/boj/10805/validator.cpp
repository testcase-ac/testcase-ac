#include "testlib.h"

using namespace std;

/*
Problem recap (for validator):
Input consists of four integers:
  h1, w1 (2 ≤ h1, w1 ≤ 50),
  h2 (1 ≤ h2 < h1),
  w2 (1 ≤ w2 < w1).
They describe an L-shaped paper; all sides are positive integers.

Nothing else (no multiple test cases, no extra spaces/lines) is specified.
We only need to validate:
  - ranges
  - strict inequalities h2 < h1, w2 < w1
  - formatting (spaces/newlines, EOF)
No additional structural/global constraints are implied that must be
checked by computing any answer; the "answer always exists" is guaranteed
by the geometry implied by the ranges and does not require extra checks.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h1 = inf.readInt(2, 50, "h1");
    inf.readSpace();
    int w1 = inf.readInt(2, 50, "w1");
    inf.readSpace();
    int h2 = inf.readInt(1, 50, "h2"); // temporary upper bound; refine below
    inf.readSpace();
    int w2 = inf.readInt(1, 50, "w2"); // temporary upper bound; refine below
    inf.readEoln();

    // Now assert the cross-constraints that depend on previously read values.
    ensuref(h2 < h1, "Constraint violated: h2 (%d) must satisfy 1 <= h2 < h1 (%d)", h2, h1);
    ensuref(w2 < w1, "Constraint violated: w2 (%d) must satisfy 1 <= w2 < w1 (%d)", w2, w1);

    inf.readEof();
}
