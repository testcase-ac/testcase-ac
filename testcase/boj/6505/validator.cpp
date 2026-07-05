#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 1;
    while (true) {
        int n = inf.readInt(0, 80, "n");
        inf.readSpace();
        long long m = inf.readLong(0LL, 1000000000LL, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        setTestCase(tc++);
        ensuref(n >= 1, "n must be positive in a non-terminal test case");
        ensuref(m >= 1, "m must be positive in a non-terminal test case");

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int p = inf.readInt(1, n, "p_i");
            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            ensuref(!seen[p], "p_i is not a permutation: duplicate value %d", p);
            seen[p] = true;
        }

        string encoded = inf.readLine();
        ensuref((int)encoded.size() == n, "encoded string length is %d, expected %d",
                (int)encoded.size(), n);
    }

    inf.readEof();
}
