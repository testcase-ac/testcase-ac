#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 70000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -n, n, "A_i");
    for (int i = 0; i < n; ++i) {
        ensuref(a[i] != 0, "A_%d must be nonzero", i + 1);
    }
    inf.readEoln();

    inf.readEof();
}
