#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readEoln();

    vector<int> h = inf.readInts(n, 0, 1000000000, "H_i");
    inf.readEoln();
    for (int i = 1; i < n; ++i) {
        ensuref(h[i - 1] >= h[i],
                "heights must be nonincreasing: H_%d=%d, H_%d=%d",
                i, h[i - 1], i + 1, h[i]);
    }

    inf.readInts(n - 1, 0, 1000000000, "A_i");
    inf.readEoln();

    inf.readInts(n - 1, 0, 1000000000, "B_i");
    inf.readEoln();

    inf.readEof();
}
