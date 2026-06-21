#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a[i] = inf.readLong(0LL, 1000000000000000LL, "a_i");
        if (i > 0) {
            ensuref(a[i - 1] <= a[i],
                    "array must be nondecreasing at positions %d and %d: %lld > %lld",
                    i, i + 1, a[i - 1], a[i]);
        }
    }
    inf.readEoln();
    inf.readEof();
}
