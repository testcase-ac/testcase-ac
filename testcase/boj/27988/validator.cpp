#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    vector<long long> x = inf.readLongs(n, -1000000000LL, 1000000000LL, "X_i");
    inf.readEoln();
    for (int i = 1; i < n; ++i) {
        ensuref(x[i - 1] < x[i],
                "X_i must be strictly increasing: X_%d=%lld, X_%d=%lld",
                i, x[i - 1], i + 1, x[i]);
    }

    inf.readLongs(n, 1LL, 1000000000LL, "L_i");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("R|Y|B", "C_i");
        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
