#include "testlib.h"

#include <vector>

using namespace std;

// Validates Code Jam Rank and File inputs, including the missing-list parity
// guarantee needed by the official problem contract.
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 10, "N");
        inf.readEoln();

        vector<int> count(2501, 0);
        for (int i = 0; i < 2 * n - 1; ++i) {
            int prev = 0;
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                int height = inf.readInt(1, 2500, "height");
                ensuref(height > prev,
                        "case %d list %d is not strictly increasing at position %d: %d after %d",
                        tc, i + 1, j + 1, height, prev);
                prev = height;
                ++count[height];
            }
            inf.readEoln();
        }

        int odd = 0;
        for (int height = 1; height <= 2500; ++height) {
            if (count[height] % 2 == 1) {
                ++odd;
            }
        }
        ensuref(odd == n,
                "case %d must have exactly N odd-count heights for the missing list, found %d",
                tc, odd);
    }

    inf.readEof();
}
