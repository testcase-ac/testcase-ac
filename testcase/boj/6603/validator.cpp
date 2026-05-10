#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read k: either 0 (end) or between 7 and 12
        int k = inf.readInt(0, 12, "k");
        if (k == 0) {
            // End marker line must be just "0"
            inf.readEoln();
            break;
        }
        // Must satisfy 6 < k < 13
        ensuref(k > 6 && k < 13,
                "k must be between 7 and 12, found %d", k);

        // After k, there must be a single space before the list
        inf.readSpace();
        // Read the set S of size k
        vector<int> S = inf.readInts(k, 1, 49, "s_i");
        inf.readEoln();

        // Check strictly increasing order
        for (int i = 1; i < k; i++) {
            ensuref(S[i] > S[i-1],
                    "Elements of S must be strictly increasing: s[%d]=%d <= s[%d]=%d",
                    i, S[i], i-1, S[i-1]);
        }

        tc++;
        ensuref(tc <= 100000,
                "Number of test cases exceeds 100000 (current %d)", tc);
    }

    inf.readEof();
    return 0;
}
