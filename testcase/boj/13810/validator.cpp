#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxN = 20000;
    constexpr int kMaxTotalN = 20000;
    constexpr long long kMaxCoord = 1000000000LL;

    int totalN = 0;
    int dataset = 0;
    while (true) {
        int n = inf.readInt(0, kMaxN, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++dataset;
        setTestCase(dataset);
        totalN += n;
        // CHECK: The statement gives no dataset-count limit; cap total futons at one largest dataset.
        ensuref(totalN <= kMaxTotalN, "sum of n exceeds %d", kMaxTotalN);

        set<pair<long long, long long>> occupied;
        for (int i = 1; i <= n; ++i) {
            long long x = inf.readLong(0LL, kMaxCoord, "x_i");
            inf.readSpace();
            long long y = inf.readLong(0LL, kMaxCoord, "y_i");
            inf.readSpace();
            string dir = inf.readToken("x|y", "dir_i");
            inf.readEoln();

            pair<long long, long long> first = {x, y};
            pair<long long, long long> second = dir == "x"
                    ? make_pair(x + 1, y)
                    : make_pair(x, y + 1);

            ensuref(occupied.insert(first).second,
                    "futon %d overlaps at cell (%lld, %lld)", i, first.first, first.second);
            ensuref(occupied.insert(second).second,
                    "futon %d overlaps at cell (%lld, %lld)", i, second.first, second.second);
        }
    }

    inf.readEof();
}
