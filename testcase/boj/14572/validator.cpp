#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 30, "k");
    inf.readSpace();
    long long d = inf.readLong(0LL, 1000000000LL, "d");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int m = inf.readInt(0, k, "m");
        inf.readSpace();
        long long skill = inf.readLong(0LL, 1000000000LL, "skill");
        inf.readEoln();

        if (m == 0) {
            inf.readEoln();
        } else {
            vector<bool> seen(k + 1, false);
            for (int j = 1; j <= m; ++j) {
                if (j > 1) {
                    inf.readSpace();
                }
                int algorithm = inf.readInt(1, k, "algorithm");
                ensuref(!seen[algorithm],
                        "student %d lists algorithm %d more than once", i, algorithm);
                seen[algorithm] = true;
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
