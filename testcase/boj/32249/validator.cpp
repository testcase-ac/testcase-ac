#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();
    // Check NM ≤ 1e6
    long long NM = 1LL * N * M;
    ensuref(NM <= 1000000LL, "N * M must be ≤ 1e6, got %lld", NM);

    // Read Alice's grid
    long long totalA = 0, totalB = 0;
    for (int i = 1; i <= N; i++) {
        // read a row token (no whitespace)
        string s = inf.readToken("[^]+", "alice_row");
        // check length
        ensuref((int)s.size() == M,
                "Alice row %d length must be %d, got %d",
                i, M, (int)s.size());
        // check characters and count
        for (int j = 0; j < M; j++) {
            char c = s[j];
            ensuref(c == 'A' || c == 'B',
                    "Alice row %d, col %d: unexpected char '%c'", i, j+1, c);
            if (c == 'A') totalA++;
            else totalB++;
        }
        inf.readEoln();
    }

    // Read Bob's grid
    for (int i = 1; i <= N; i++) {
        string s = inf.readToken("[^]+", "bob_row");
        ensuref((int)s.size() == M,
                "Bob row %d length must be %d, got %d",
                i, M, (int)s.size());
        for (int j = 0; j < M; j++) {
            char c = s[j];
            ensuref(c == 'A' || c == 'B',
                    "Bob row %d, col %d: unexpected char '%c'", i, j+1, c);
            if (c == 'A') totalA++;
            else totalB++;
        }
        inf.readEoln();
    }

    // Check total counts: exactly NM A's and NM B's
    ensuref(totalA == NM,
            "Total count of 'A' must be N*M = %lld, got %lld", NM, totalA);
    ensuref(totalB == NM,
            "Total count of 'B' must be N*M = %lld, got %lld", NM, totalB);

    // Read Q
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read Q queries
    for (int i = 1; i <= Q; i++) {
        int r1 = inf.readInt(1, N, "r1");
        inf.readSpace();
        int c1 = inf.readInt(1, M, "c1");
        inf.readSpace();
        int r2 = inf.readInt(1, N, "r2");
        inf.readSpace();
        int c2 = inf.readInt(1, M, "c2");
        inf.readEoln();
        // No further checks: positions in range suffices
    }

    inf.readEof();
    return 0;
}
