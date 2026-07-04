#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        int totalHikers = 0;
        set<pair<int, long long>> startingPlaceAndPeriod;
        for (int i = 1; i <= n; ++i) {
            int d = inf.readInt(1, 359, "D_i");
            inf.readSpace();
            int h = inf.readInt(1, 2, "H_i");
            inf.readSpace();
            long long m = inf.readLong(1LL, 1000000000LL, "M_i");
            inf.readEoln();

            totalHikers += h;
            ensuref(totalHikers <= 2,
                    "case %d has more than 2 hikers after group %d",
                    caseIndex, i);

            for (int j = 0; j < h; ++j) {
                long long period = m + j;
                ensuref(startingPlaceAndPeriod.insert({d, period}).second,
                        "case %d has duplicate hiker at D=%d with period %lld",
                        caseIndex, d, period);
            }
        }
    }

    inf.readEof();
}
