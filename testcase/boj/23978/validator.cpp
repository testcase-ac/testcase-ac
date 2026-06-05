#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(a[i - 1] < a[i],
                "a_i must be strictly increasing: a[%d]=%d, a[%d]=%d",
                i, a[i - 1], i + 1, a[i]);
    }

    inf.readEof();
}
