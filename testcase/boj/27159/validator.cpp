#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 33, "N");
    inf.readEoln();

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        x[i] = inf.readInt(3, 35, "x_i");
        if (i > 0) {
            ensuref(x[i - 1] < x[i],
                    "x_i must be strictly increasing: x_%d=%d, x_%d=%d",
                    i, x[i - 1], i + 1, x[i]);
        }
    }
    inf.readEoln();
    inf.readEof();
}
