#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        int hikers = 0;
        set<pair<int, long long>> seenHikers;
        for (int i = 1; i <= n; ++i) {
            int d = inf.readInt(1, 359, "D_i");
            inf.readSpace();
            int h = inf.readInt(1, 10, "H_i");
            inf.readSpace();
            long long m = inf.readLong(1LL, 1000000000LL, "M_i");
            inf.readEoln();

            hikers += h;
            ensuref(hikers <= 10, "test case %d has more than 10 hikers", tc);

            for (int offset = 0; offset < h; ++offset) {
                long long revolutionTime = m + offset;
                ensuref(seenHikers.insert({d, revolutionTime}).second,
                        "duplicate hiker at D=%d with revolution time %lld",
                        d, revolutionTime);
            }
        }
    }

    inf.readEof();
    return 0;
}
