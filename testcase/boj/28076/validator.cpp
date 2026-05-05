#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem understanding (for validator):

- N (number of power strips): 1 ≤ N ≤ 200000.
- Each strip has ai outlets: 2 ≤ ai ≤ 1e8.
- They have many types from 2 to 1e8 outlets, but input just gives N and a_i.
- Geometric/stacking description only affects solution, not input structure.
- There is no mention of multiple test cases.
- Output is a single integer (not relevant for validator).

Thus the validator must check:
- Single test.
- First line: integer N in [1, 200000], canonical decimal, no extra tokens.
- Second line: exactly N integers a_i in [2, 1e8], canonical decimal.
- Strict whitespace: spaces between numbers, newline at end of each line,
  and EOF immediately after the second line's EOLN.
- No additional global structural properties are specified that depend on
  arrangement or guarantee of answer existence beyond trivial (always exists)
  – and that does not restrict input further.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read array a_1..a_N on the second line
    vector<long long> a = inf.readLongs(N, 2LL, 100000000LL, "a_i");
    inf.readEoln();

    // No extra content allowed
    inf.readEof();
}
