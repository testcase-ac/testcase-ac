#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(0, 1000000, "K");
    inf.readEoln();

    vector<int> x = inf.readInts(n, 1, 1000000, "X_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(x[i - 1] < x[i],
                "X_i must be strictly increasing: X_%d=%d, X_%d=%d",
                i, x[i - 1], i + 1, x[i]);
    }

    inf.readEof();
}
