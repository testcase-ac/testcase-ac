#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 10000, "N");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            int x = inf.readInt(-30000, 30000, "x_i");
            inf.readSpace();
            int y = inf.readInt(-30000, 30000, "y_i");
            inf.readEoln();
            (void)x;
            (void)y;
        }
    }

    inf.readEof();
}
