#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, K
    int N = inf.readInt(2, 50, "N"); // N ≥ 2 because 1 ≤ K < N
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readSpace();
    int K = inf.readInt(1, 49, "K"); // K < N ≤ 50, so K ≤ 49
    inf.readEoln();

    ensuref(K < N, "Constraint violated: K (%d) must be less than N (%d)", K, N);

    // Read N lines of length-M strings over {R,S,P}
    vector<string> a(N);
    for (int i = 0; i < N; ++i) {
        // Read as arbitrary line, then validate manually (simpler than regex with escaped space)
        string s = inf.readToken("[^]+", "a_i");
        inf.readEoln();

        ensuref((int)s.size() == M,
                "Line %d: string length must be exactly M = %d, but got %d",
                i + 1, M, (int)s.size());
        for (int j = 0; j < M; ++j) {
            char c = s[j];
            ensuref(c == 'R' || c == 'S' || c == 'P',
                    "Line %d, position %d: invalid character '%c', expected one of {R,S,P}",
                    i + 1, j + 1, c);
        }
        a[i] = s;
    }

    // Global property from statement:
    // It is NOT guaranteed that gifts can always be distributed.
    // It only says what to do "if" it is possible, and that maximum rounds is M.
    // There is no additional global structural guarantee that must be enforced
    // (e.g., connectivity, existence of answer, etc.) beyond local format/constraints.
    // Therefore, no extra simulation or global validation is required.

    inf.readEof();
}
