#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> x(n);
    x[0] = inf.readInt(0, 0, "x_0");
    for (int i = 1; i < n; ++i) {
        inf.readSpace();
        x[i] = inf.readInt(1, 1000000000, "x_i");
        ensuref(x[i - 1] < x[i],
                "positions must be distinct and increasing: x[%d]=%d, x[%d]=%d",
                i - 1, x[i - 1], i, x[i]);
    }
    inf.readEoln();
    inf.readEof();
}
