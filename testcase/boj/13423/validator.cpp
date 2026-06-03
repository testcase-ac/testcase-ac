#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 1000, "N");
        inf.readEoln();

        // CHECK: T has no statement upper bound; cap total points to keep numeric inputs practical.
        totalN += n;
        ensuref(totalN <= 1000000, "total N exceeds practical cap: %d", totalN);

        vector<int> x = inf.readInts(n, -100000000, 100000000, "X_i");
        inf.readEoln();

        set<int> seen;
        for (int i = 0; i < n; ++i) {
            ensuref(seen.insert(x[i]).second, "duplicate point position at index %d: %d", i + 1, x[i]);
        }
    }

    inf.readEof();
}
