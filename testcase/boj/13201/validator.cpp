#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and K
        int N = inf.readInt(2, 100, "N");
        inf.readSpace();
        int K = inf.readInt(1, 1000, "K");
        inf.readEoln();

        // Read airport codes
        vector<string> codes(N);
        for (int i = 0; i < N; i++) {
            string code = inf.readToken("[A-Z]{3}", "airport_code");
            inf.readEoln();
            codes[i] = code;
        }
        // Check uniqueness of codes
        {
            set<string> st(codes.begin(), codes.end());
            ensuref((int)st.size() == N,
                    "Duplicate airport codes found");
        }
        // Find ICN index
        int icn_idx = -1;
        for (int i = 0; i < N; i++) {
            if (codes[i] == "ICN") {
                icn_idx = i;
                break;
            }
        }
        ensuref(icn_idx != -1,
                "ICN must appear exactly once among airport codes");

        // Read flight counts S_ij
        vector<vector<int>> S(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            vector<int> row = inf.readInts(N, 0, 100, "S_ij");
            inf.readEoln();
            for (int j = 0; j < N; j++) {
                ensuref(!(i == j && row[j] != 0),
                        "S_%d%d must be 0 (no self-flights), got %d", i+1, j+1, row[j]);
                S[i][j] = row[j];
            }
        }

        // Validate existence of at least one path of length K from ICN
        bitset<100> cur, nxt;
        cur.reset();
        cur.set(icn_idx);
        for (int step = 1; step <= K; step++) {
            nxt.reset();
            for (int u = 0; u < N; u++) {
                if (!cur.test(u)) continue;
                for (int v = 0; v < N; v++) {
                    if (S[u][v] > 0) {
                        nxt.set(v);
                    }
                }
            }
            cur = nxt;
            // Early fail if no reachable airports at this step and it's needed
            if (step < K && cur.none()) {
                ensuref(false,
                        "No possible path of length %d from ICN (stuck at step %d)", K, step);
            }
        }
        ensuref(cur.any(),
                "No possible path of length %d from ICN", K);
    }

    inf.readEof();
    return 0;
}
