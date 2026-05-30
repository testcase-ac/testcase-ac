#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N (number of singers) and M (number of assistant PDs)
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // For each assistant PD, read their sequence
    for (int i = 0; i < M; i++) {
        // k = number of singers this PD has ordered
        int k = inf.readInt(0, N, "k_i");
        vector<bool> seen(N + 1, false);
        if (k > 0) {
            inf.readSpace();
            // Read exactly k singer IDs
            for (int j = 0; j < k; j++) {
                if (j > 0) inf.readSpace();
                int singer = inf.readInt(1, N, "s_i_j");
                ensuref(!seen[singer],
                        "duplicate singer %d in PD sequence %d", singer, i + 1);
                seen[singer] = true;
            }
        }
        // End of this PD's line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
