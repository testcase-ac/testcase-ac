#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int p = inf.readInt(0, n - 1, "P_i");
        ensuref(!seen[p], "P[%d] duplicates value %d", i, p);
        seen[p] = true;
    }
    inf.readEoln();
    inf.readEof();
}
