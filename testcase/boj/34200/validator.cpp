#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "N");
    inf.readEoln();

    int prev = 0;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 250000, "X_i");
        ensuref(i == 1 || prev < x, "X_%d=%d is not greater than X_%d=%d", i, x, i - 1, prev);
        prev = x;
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
