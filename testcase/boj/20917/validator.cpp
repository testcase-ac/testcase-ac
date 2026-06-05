#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 200000, "n");
        inf.readSpace();
        int s = inf.readInt(2, n, "s");
        inf.readEoln();

        vector<int> x = inf.readInts(n, 1, 1000000000, "x_i");
        inf.readEoln();

        set<int> seen;
        for (int i = 0; i < n; ++i) {
            ensuref(seen.insert(x[i]).second,
                    "duplicate outlet position at index %d: %d", i + 1, x[i]);
        }
    }

    inf.readEof();
}
