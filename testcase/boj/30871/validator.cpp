#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 200000;
    const long long maxValue = 1000000000000000000LL;

    int n = inf.readInt(1, maxN, "N");
    inf.readEoln();

    vector<long long> l = inf.readLongs(n, 1LL, maxValue, "L_i");
    inf.readEoln();

    vector<long long> r = inf.readLongs(n, 1LL, maxValue, "R_i");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        ensuref(l[i] <= r[i], "L_%d must be <= R_%d, got %lld > %lld",
                i + 1, i + 1, l[i], r[i]);
    }

    inf.readEof();
}
