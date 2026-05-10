#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem recap (for validator logic):

- Single test case.
- N (1 ≤ N ≤ 10,000).
- A_i (2 ≤ A_i ≤ 100,000), integers.
- Each stick can be used at most once.
- You may optionally reduce ONE stick's length by exactly 1 (from A_i to A_i-1) at most once per stick;
  i.e., each stick may become either A_i or A_i-1 (but not A_i-2 etc.).
- Can't join multiple sticks to form one side; each side is exactly one stick.
- Rectangles are axis-agnostic: 2 equal sides for length, 2 equal sides for width.
- You may build zero or more rectangles; some sticks may remain unused.
- Objective: maximize the sum of areas of all rectangles.

From validator perspective:
- Only need to validate format and numeric constraints plus global format rules.
- No additional global guarantees (like "answer always exists") beyond standard input constraints.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case as per statement
    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read second line: N integers A_i in [2, 100000]
    vector<int> a = inf.readInts(n, 2, 100000, "A_i");
    inf.readEoln();

    // No further structural/global properties to validate for this problem.

    inf.readEof();
}
