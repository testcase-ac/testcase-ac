#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read multiple test cases until EOF
    while (!inf.eof()) {
        ++tc;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);
        setTestCase(tc);

        // Read N and K
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int K = inf.readInt(1, 100000, "K");
        inf.readEoln();

        // Read the array X of size N
        vector<int> X = inf.readInts(N, -100, 100, "X_i");
        inf.readEoln();

        bool hasP = false;
        for (int i = 0; i < K; i++) {
            // Read command type: C or P
            string cmd = inf.readToken("C|P", "cmd");
            inf.readSpace();
            if (cmd == "C") {
                // Change command: C i V
                int idx = inf.readInt(1, N, "C_i");
                inf.readSpace();
                int V = inf.readInt(-100, 100, "C_V");
                inf.readEoln();
            } else {
                // Product query: P i j
                hasP = true;
                int l = inf.readInt(1, N, "P_i");
                inf.readSpace();
                int r = inf.readInt(1, N, "P_j");
                ensuref(l <= r, "In P command, left index %d > right index %d", l, r);
                inf.readEoln();
            }
        }
        ensuref(hasP, "Test case %d: no P command found", tc);
    }

    inf.readEof();
    return 0;
}
