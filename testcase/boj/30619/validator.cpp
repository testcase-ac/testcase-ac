#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "A_i");
        ensuref(!seen[a], "A must be a permutation: value %d appears more than once", a);
        seen[a] = 1;
    }
    inf.readEoln();

    int m = inf.readInt(1, 300, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        int r = inf.readInt(l, n, "R");
        inf.readEoln();
    }

    inf.readEof();
}
