#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "A_i");
    inf.readEoln();

    ensuref(a.back() == 1, "A_N must be 1, found %d", a.back());

    int suffixMax = a.back();
    for (int i = n - 2; i >= 0; --i) {
        ensuref(a[i] <= suffixMax + 1,
                "no permutation can have A_%d = %d with later maximum %d",
                i + 1, a[i], suffixMax);
        suffixMax = max(suffixMax, a[i]);
    }

    inf.readEof();
}
