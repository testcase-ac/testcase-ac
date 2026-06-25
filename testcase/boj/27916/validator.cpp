#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 300000;
    const int maxQ = 300000;
    const long long maxCoord = 1000000000LL;

    int n = inf.readInt(1, maxN, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    int q = inf.readInt(1, maxQ, "Q");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, maxCoord, "A_i");
    inf.readEoln();
    for (int i = 1; i < n; ++i) {
        ensuref(a[i - 1] < a[i],
                "A_i must be strictly increasing: A_%d=%lld, A_%d=%lld",
                i, a[i - 1], i + 1, a[i]);
    }

    inf.readLongs(q, 0LL, maxCoord, "X_i");
    inf.readEoln();

    inf.readEof();
}
