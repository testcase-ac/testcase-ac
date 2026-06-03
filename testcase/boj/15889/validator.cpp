#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30000, "n");
    inf.readEoln();

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        x[i] = inf.readInt(0, 1000000, "x_i");
    }
    inf.readEoln();

    ensuref(x[0] == 0, "x_1 must be 0, got %d", x[0]);
    for (int i = 1; i < n; ++i) {
        // CHECK: The statement gives soldiers in the line from Ukje and refers to
        // the Nth soldier from the left; equal coordinates are explicitly allowed.
        ensuref(x[i - 1] <= x[i],
                "coordinates must be nondecreasing: x_%d=%d, x_%d=%d",
                i, x[i - 1], i + 1, x[i]);
    }

    if (n > 1) {
        for (int i = 0; i < n - 1; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 1000000, "range_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
