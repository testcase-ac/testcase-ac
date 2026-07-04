#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readLong(1LL, (1LL << 30) - 1, "C");
    inf.readEoln();

    vector<long long> weights(n);
    for (int i = 0; i < n; ++i) {
        weights[i] = inf.readLong(1LL, (1LL << 31) - 1, "weight");
        inf.readEoln();

        if (i > 0) {
            ensuref(weights[i - 1] <= weights[i],
                    "weights must be non-decreasing: weight[%d]=%lld, weight[%d]=%lld",
                    i, weights[i - 1], i + 1, weights[i]);
        }
        if (i >= 2) {
            ensuref(weights[i] >= weights[i - 1] + weights[i - 2],
                    "weight[%d]=%lld must be at least weight[%d]+weight[%d]=%lld",
                    i + 1, weights[i], i, i - 1, weights[i - 1] + weights[i - 2]);
        }
    }

    inf.readEof();
}
