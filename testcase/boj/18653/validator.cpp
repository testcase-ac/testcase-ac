#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem-specific notes for validation:

- T test cases, 1 ≤ T ≤ 100.
- For each test:
    - 2 ≤ n, m ≤ 100.
    - Then exactly H = 4n + 3 lines follow.
    - Each line has length ≤ Wmax = 6m + 3, and has no trailing spaces.
    - Allowed characters:
        - All lines: ' ', '+', '-', '/', '\', '*'
    - Lines with odd index in statement (1-based) are "vertex + horizontal edges" lines.
      The input description does NOT forbid '*' here, and samples do have '*'
      on such lines (cell centers on "middle" vertex lines). So we must NOT
      restrict characters on those lines beyond the global allowed set.
    - Lines with even index in statement are "diagonal edges" lines; again
      only the global allowed characters appear.

- It is guaranteed that every non-special cell has no traversable edge.
  This is a promise for solutions, not something we can feasibly and reliably
  check from the ASCII art in a validator, since we lack a precise mapping
  from '*' positions to cells and from edges to "traversable / untraversable"
  in graph terms. We therefore do not attempt to enforce this.

- Sum of numbers of special cells over all test cases ≤ 3000.
- There is no explicit requirement that there are at least 2 special cells
  per test; the sum over "every two special cells" is then 0 if fewer than 2
  exist. So we do NOT enforce specialCnt ≥ 2 for each test case.

- We must enforce canonical numeric format; readInt already does this.

- Global formatting: we read line-by-line with readLine (which consumes EOLN),
  then finally readEof().

Implementation choices:

- For each of the H lines we:
    * read with regex "[^]*" to allow arbitrary characters (no trailing EOLN),
      and no trailing spaces promised by statement.
    * check length ≤ Wmax.
    * check each character is one of the allowed six characters.
    * count '*' occurrences.

- We do NOT attempt to parse '+' / '---' patterns, since the problem statement
  allows variable amount of spaces and only gives a descriptive (not rigid)
  format; the previous validator failed by being too restrictive.

*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long totalSpecial = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "n");
        inf.readSpace();
        int m = inf.readInt(2, 100, "m");
        inf.readEoln();

        int H = 4 * n + 3;
        int Wmax = 6 * m + 3;

        for (int i = 0; i < H; ++i) {
            // Read full line including spaces, no trailing spaces per statement.
            string line = inf.readLine("[^]*", "line");

            ensuref((int)line.size() <= Wmax,
                    "Test case %d, line %d: length %d exceeds max %d for m=%d",
                    tc, i + 1, (int)line.size(), Wmax, m);

            for (int j = 0; j < (int)line.size(); ++j) {
                char c = line[j];
                ensuref(c == ' ' || c == '+' || c == '-' ||
                        c == '/' || c == '\\' || c == '*',
                        "Test case %d, invalid character '%c' at line %d, col %d",
                        tc, c, i + 1, j + 1);
                if (c == '*') {
                    totalSpecial++;
                    ensuref(totalSpecial <= 3000,
                            "Total number of special cells across all tests exceeded 3000 (now %lld)",
                            totalSpecial);
                }
            }
        }
    }

    inf.readEof();
}
