#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readSpace();
    int m = inf.readInt(0, 10, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, k, "c_i");
    }
    inf.readEoln();

    for (int j = 0; j < m; ++j) {
        int r = inf.readInt(1, n, "r_j");
        vector<bool> seen(n + 1, false);
        for (int i = 0; i < r; ++i) {
            inf.readSpace();
            int region = inf.readInt(1, n, "region");
            ensuref(!seen[region],
                    "equipment %d covers region %d more than once",
                    j + 1,
                    region);
            seen[region] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
