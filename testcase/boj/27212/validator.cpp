#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int c = inf.readInt(2, 16, "c");
    inf.readEoln();

    vector<vector<long long>> w(c, vector<long long>(c));
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            w[i][j] = inf.readLong(1LL, 1000000000LL, "w_ij");
        }
        inf.readEoln();
    }

    for (int i = 0; i < c; ++i) {
        for (int j = i + 1; j < c; ++j) {
            ensuref(w[i][j] == w[j][i],
                    "w is not symmetric at (%d, %d): %lld != %lld",
                    i + 1, j + 1, w[i][j], w[j][i]);
        }
    }

    inf.readInts(n, 1, c, "a_i");
    inf.readEoln();

    inf.readInts(m, 1, c, "b_i");
    inf.readEoln();

    inf.readEof();
}
