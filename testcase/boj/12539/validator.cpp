#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        inf.readInt(100, 500, "M");
        inf.readEoln();

        vector<int> prices = inf.readInts(12, 1, 250, "P");
        inf.readEoln();

        set<int> uniquePrices(prices.begin(), prices.end());
        ensuref(uniquePrices.size() == prices.size(),
                "prices must be different within case %d", tc);
    }

    inf.readEof();
}
