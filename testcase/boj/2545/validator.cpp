#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Between test cases, there is a blank line.
        // The statement says: "각 테스트 케이스는 빈 줄로 구분되며"
        // From the sample format, there is also a blank line after T and
        // before the *first* test case.
        //
        // So: Before every test case (including the first), we expect exactly one
        // empty line (a line of length 0, just '\n').
        string blank = inf.readLine("[^]*", "blank_line_before_case");
        ensuref(blank.size() == 0,
                "Expected an empty blank line before test case %d, but got non-empty content",
                tc + 1);

        // Read A, B, C, D for this test case
        long long A = inf.readLong(1LL, (long long)1e18, "A");
        inf.readSpace();
        long long B = inf.readLong(1LL, (long long)1e18, "B");
        inf.readSpace();
        long long C = inf.readLong(1LL, (long long)1e18, "C");
        inf.readSpace();
        // D temporary broad upper bound, refined below after reading A,B,C:
        long long D = inf.readLong(0LL, (long long)3e18, "D");
        inf.readEoln();

        // Constraint: 0 ≤ D ≤ A + B + C - 3
        __int128 sum = (__int128)A + (__int128)B + (__int128)C;
        __int128 maxD128 = sum - 3;
        // Since A,B,C >= 1, we have sum >= 3, so maxD128 >= 0.
        ensuref(maxD128 >= 0,
                "Internal error: A+B+C-3 is negative in test case %d (A=%lld,B=%lld,C=%lld)",
                tc + 1, A, B, C);
        long long maxD = (long long)maxD128;
        ensuref(D <= maxD,
                "D out of allowed range 0..A+B+C-3 in test case %d: D=%lld, max allowed=%lld (A=%lld,B=%lld,C=%lld)",
                tc + 1, D, maxD, A, B, C);

        // Global guarantee: the maximum remaining volume (<= A*B*C) fits in signed 64-bit.
        __int128 vol = (__int128)A * (__int128)B * (__int128)C;
        long long maxLL = numeric_limits<long long>::max();
        ensuref(vol <= (__int128)maxLL,
                "Initial volume A*B*C does not fit in signed 64-bit integer in test case %d (A=%lld,B=%lld,C=%lld)",
                tc + 1, A, B, C);
    }

    inf.readEof();
}
