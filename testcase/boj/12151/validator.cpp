#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int C = inf.readInt(1, 1, "C");
        inf.readSpace();
        int D = inf.readInt(1, 5, "D");
        inf.readSpace();
        int V = inf.readInt(1, 30, "V");
        inf.readEoln();

        vector<int> denominations = inf.readInts(D, 1, V, "denomination");
        inf.readEoln();

        for (int i = 1; i < D; ++i) {
            ensuref(denominations[i - 1] < denominations[i],
                    "denominations must be strictly ascending, but d[%d]=%d and d[%d]=%d",
                    i, denominations[i - 1], i + 1, denominations[i]);
        }
    }

    inf.readEof();
}
