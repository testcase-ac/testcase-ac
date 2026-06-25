#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxValue = 1000000000000000000LL;

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 0LL, kMaxValue, "a_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(n, 0LL, kMaxValue, "b_i");
    inf.readEoln();

    bool hasDifferentPair = false;
    for (int i = 0; i < n; ++i) {
        ensuref(b[i] <= a[i], "b_%d (%lld) must not exceed a_%d (%lld)",
                i + 1, b[i], i + 1, a[i]);
        hasDifferentPair = hasDifferentPair || (a[i] != b[i]);
    }

    ensuref(hasDifferentPair, "at least one equation must have a_i != b_i");

    inf.readEof();
}
