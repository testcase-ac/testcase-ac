#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "H");
    inf.readEoln();

    vector<int> d = inf.readInts(n, 1, 1000000, "d_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(d[i - 1] <= d[i], "d_i must be nondecreasing at index %d: %d > %d", i + 1, d[i - 1], d[i]);
    }

    inf.readEof();
}
