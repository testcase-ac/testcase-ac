#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc+1);

        // 2. Read N
        long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
        inf.readEoln();

        // 3. Read X
        long long max_X = min(N-1, 1000LL);
        int X = inf.readInt(1, int(max_X), "X");
        inf.readEoln();

        // 4. Read P_1 ... P_X
        vector<long long> P(X);
        if (X > 0) {
            P = inf.readLongs(X, 1LL, N-1, "P_i");
            inf.readEoln();
        }

        // 5. Check strictly increasing order
        for (int i = 0; i < X; ++i) {
            if (i > 0) {
                ensuref(P[i] > P[i-1], 
                    "P_i not strictly increasing: P[%d]=%lld, P[%d]=%lld", i, P[i], i-1, P[i-1]);
            }
        }
    }

    inf.readEof();
}
