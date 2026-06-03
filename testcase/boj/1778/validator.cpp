#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 0;
    while (true) {
        int n = inf.readInt(0, 50000, "n");
        inf.readSpace();
        long long maxPairs = 1LL * n * (n - 1) / 2;
        long long m = inf.readLong(0LL, maxPairs, "m");
        inf.readEoln();

        if (n == 0) {
            ensuref(m == 0, "terminating case must be exactly 0 0");
            break;
        }

        setTestCase(++caseIndex);
        set<pair<int, int>> pairs;
        for (long long i = 0; i < m; ++i) {
            int a = inf.readInt(1, n, "i");
            inf.readSpace();
            int b = inf.readInt(1, n, "j");
            inf.readEoln();

            ensuref(a != b, "self-pair at relation %lld: (%d, %d)", i + 1, a, b);
            auto edge = minmax(a, b);
            ensuref(pairs.insert(edge).second,
                    "duplicate pair at relation %lld: (%d, %d)", i + 1, a, b);
        }
    }

    inf.readEof();
}
