#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "m");
    inf.readEoln();

    long long totalListed = 0;
    for (int i = 1; i <= m; ++i) {
        int mi = inf.readInt(1, n, "m_i");
        totalListed += mi;
        ensuref(totalListed <= 200000,
                "sum of m_i exceeds 200000 after observation %d: %lld", i,
                totalListed);

        set<int> seen;
        for (int j = 1; j <= mi; ++j) {
            inf.readSpace();
            int cow = inf.readInt(1, n, "cow");
            // CHECK: "some of his cows" is interpreted as no repeated cow within one observation.
            ensuref(seen.insert(cow).second,
                    "cow %d appears more than once in observation %d", cow, i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
