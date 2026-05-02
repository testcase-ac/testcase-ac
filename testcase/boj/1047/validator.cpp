#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 40;
    const int MAXV = 1000000;

    int N = inf.readInt(2, MAXN, "N");
    inf.readEoln();

    vector<int> xs(N), ys(N), ls(N);

    for (int i = 0; i < N; ++i) {
        xs[i] = inf.readInt(1, MAXV, "x_i");
        inf.readSpace();
        ys[i] = inf.readInt(1, MAXV, "y_i");
        inf.readSpace();
        ls[i] = inf.readInt(1, MAXV, "l_i");
        inf.readEoln();
    }

    // Check all x are distinct
    {
        vector<int> tmp = xs;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < N; ++i) {
            ensuref(tmp[i] != tmp[i - 1],
                    "x-coordinates must be pairwise distinct, but value %d repeats",
                    tmp[i]);
        }
    }

    // Check all y are distinct
    {
        vector<int> tmp = ys;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < N; ++i) {
            ensuref(tmp[i] != tmp[i - 1],
                    "y-coordinates must be pairwise distinct, but value %d repeats",
                    tmp[i]);
        }
    }

    inf.readEof();
}
