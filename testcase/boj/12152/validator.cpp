#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int c = inf.readInt(1, 100, "C");
        inf.readSpace();
        int d = inf.readInt(1, 100, "D");
        inf.readSpace();
        long long v = inf.readLong(1LL, 1000000000LL, "V");
        inf.readEoln();

        vector<long long> denominations = inf.readLongs(d, 1LL, v, "denomination");
        inf.readEoln();

        for (int i = 1; i < d; ++i) {
            ensuref(denominations[i - 1] < denominations[i],
                    "denominations must be distinct and ascending: index %d has %lld after %lld",
                    i + 1, denominations[i], denominations[i - 1]);
        }
    }

    inf.readEof();
}
