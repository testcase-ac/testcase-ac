#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "N");
        inf.readEoln();

        vector<int> values = inf.readInts(n, 1, n, "L_i");
        inf.readEoln();

        vector<bool> seen(n + 1, false);
        for (int i = 0; i < n; ++i) {
            ensuref(!seen[values[i]], "duplicate L_%d value: %d", i + 1, values[i]);
            seen[values[i]] = true;
        }
    }

    inf.readEof();
}
