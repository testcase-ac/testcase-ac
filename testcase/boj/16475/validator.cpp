#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readSpace();
    int k = inf.readInt(0, n, "k");
    inf.readSpace();
    int l = inf.readInt(0, m, "l");
    inf.readSpace();
    int p = inf.readInt(1, 10, "p");
    inf.readEoln();

    vector<bool> isTrap(n + 1, false);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int x = inf.readInt(1, n, "trap_region");
        ensuref(!isTrap[x], "duplicate trap region: %d", x);
        isTrap[x] = true;
    }
    inf.readEoln();

    // CHECK: The statement does not forbid self-loops or duplicate directed roads.
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 10000, "c");
        inf.readEoln();
    }

    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    inf.readInt(1, n, "e");
    inf.readEoln();

    ensuref(!isTrap[s], "start region must not be a trap region: %d", s);

    inf.readEof();
}
