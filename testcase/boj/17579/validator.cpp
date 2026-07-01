#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 100, "n");
        inf.readSpace();
        int m = inf.readInt(0, 10, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++datasets;
        setTestCase(datasets);
        ensuref(datasets <= 100, "too many datasets: %d", datasets);
        ensuref(1 <= n, "n must be positive in a dataset, got %d", n);
        ensuref(1 <= m, "m must be positive in a dataset, got %d", m);

        vector<long long> amounts = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
        inf.readEoln();
        set<long long> uniqueAmounts(amounts.begin(), amounts.end());
        ensuref((int)uniqueAmounts.size() == n, "a_i values must be distinct");

        inf.readLongs(m, 1LL, 100000000LL, "w_j");
        inf.readEoln();
    }

    inf.readEof();
}
