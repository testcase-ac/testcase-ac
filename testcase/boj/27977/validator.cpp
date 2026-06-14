#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(5, 200000, "L");
    inf.readSpace();
    int n = inf.readInt(3, min(l - 1, 100000), "N");
    inf.readSpace();
    int k = inf.readInt(0, n, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, l - 1, "A_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(a[i - 1] < a[i],
                "A_i must be strictly increasing: A_%d=%d, A_%d=%d",
                i, a[i - 1], i + 1, a[i]);
    }

    inf.readEof();
}
