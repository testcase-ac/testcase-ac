#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n - 1, "M");
    inf.readSpace();
    int k = inf.readInt(1, 3000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        inf.readInt(0, n - 1, "G_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "Y_i");
        inf.readEoln();
    }

    int l = inf.readInt(0, n - 1, "L");
    inf.readEoln();

    vector<bool> unstable(n, false);
    for (int i = 1; i <= l; ++i) {
        int x = inf.readInt(0, n - 1, "X_i");
        inf.readEoln();

        ensuref(x != 0, "unstable dimension X_%d is 0", i);
        ensuref(x != m, "unstable dimension X_%d is M: %d", i, m);
        ensuref(!unstable[x], "duplicate unstable dimension X_%d: %d", i, x);
        unstable[x] = true;
    }

    inf.readEof();
}
