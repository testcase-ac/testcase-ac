#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        // CHECK: The statement does not bound T or sum(N); cap total N to keep
        // generated inputs within the repo's practical scalar-token policy.
        ensuref(totalN <= 2500000, "sum of N exceeds 2500000");

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int p = inf.readInt(1, n, "P_i");
            inf.readEoln();

            ensuref(!seen[p], "P_%d is duplicated: %d", i, p);
            seen[p] = true;
        }
    }

    inf.readEof();
}
