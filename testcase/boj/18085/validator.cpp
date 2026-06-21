#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 200000;
    const int maxTotalM = 200000;
    const long long maxD = 1000000000LL;

    int n = inf.readInt(2, maxN, "n");
    inf.readEoln();

    long long totalM = 0;
    for (int i = 1; i <= n; ++i) {
        int m = inf.readInt(1, maxTotalM, "m_i");
        totalM += m;
        ensuref(totalM <= maxTotalM,
                "sum of m_i exceeds %d after individual %d", maxTotalM, i);

        set<long long> descriptors;
        for (int j = 1; j <= m; ++j) {
            inf.readSpace();
            long long d = inf.readLong(1LL, maxD, "d_i_j");
            ensuref(descriptors.insert(d).second,
                    "duplicate descriptor %lld for individual %d", d, i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
