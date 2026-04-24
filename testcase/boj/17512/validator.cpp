#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 250000, "T");
    inf.readEoln();

    // Track sum of N^2 across all test cases
    long long sumSquares = 0;
    const long long MAX_SUM_SQUARES = 2500000LL;

    for (int tc = 1; tc <= T; ++tc) {
        // Mark current test case for better error messages
        setTestCase(tc);

        // Read N
        int N = inf.readInt(1, 512, "N");
        inf.readEoln();

        // Update and check global sum of N^2
        sumSquares += (long long)N * (long long)N;
        ensuref(sumSquares <= MAX_SUM_SQUARES,
                "Sum of N^2 over all test cases exceeds %lld (got %lld)",
                MAX_SUM_SQUARES, sumSquares);

        // Read the matchup matrix
        vector<string> s(N);
        for (int i = 0; i < N; ++i) {
            // Read the i-th row as a full line
            string row = inf.readLine("[^]+", "row");
            // Check length
            ensuref((int)row.size() == N,
                    "In test case %d, row %d has length %d but expected %d",
                    tc, i+1, (int)row.size(), N);
            // Check each character
            for (int j = 0; j < N; ++j) {
                char c = row[j];
                ensuref(c == 'W' || c == 'L' || c == '-',
                        "In test case %d, invalid character '%c' at row %d, column %d",
                        tc, c, i+1, j+1);
            }
            s[i] = row;
        }

        // Validate diagonal and symmetry conditions
        for (int i = 0; i < N; ++i) {
            // Diagonal must be '-'
            ensuref(s[i][i] == '-',
                    "In test case %d, diagonal element at (%d,%d) is '%c' but expected '-'",
                    tc, i+1, i+1, s[i][i]);
            // Symmetry: if s[i][j] is W then s[j][i] must be L, and vice versa
            for (int j = i + 1; j < N; ++j) {
                char c1 = s[i][j], c2 = s[j][i];
                bool ok = (c1 == 'W' && c2 == 'L') || (c1 == 'L' && c2 == 'W');
                ensuref(ok,
                        "In test case %d, inconsistent results at (%d,%d)='%c' and (%d,%d)='%c'",
                        tc, i+1, j+1, c1, j+1, i+1, c2);
            }
        }
    }

    inf.readEof();
    return 0;
}
