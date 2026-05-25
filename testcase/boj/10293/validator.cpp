#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 5, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int L = inf.readInt(1, 200000, "L");
        inf.readEoln();

        vector<char> liveGroup(N + 1, true);

        for (int op = 1; op <= L; ++op) {
            int K = inf.readInt(1, 2, "K");

            if (K == 1) {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int Y = inf.readInt(1, N, "Y");
                inf.readEoln();

                ensuref(X != Y, "merge operation %d uses the same group label X=Y=%d", op, X);
                ensuref(liveGroup[X], "merge operation %d uses non-existing group X=%d", op, X);
                ensuref(liveGroup[Y], "merge operation %d uses non-existing group Y=%d", op, Y);

                liveGroup[Y] = false;
            } else {
                inf.readSpace();
                inf.readInt(1, N, "J");
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
