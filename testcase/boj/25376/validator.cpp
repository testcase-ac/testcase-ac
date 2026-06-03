#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 20, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "A_i");
    }
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int c = inf.readInt(0, n - 1, "C_i");
        set<int> affected;
        for (int j = 1; j <= c; ++j) {
            inf.readSpace();
            int b = inf.readInt(1, n, "B_i_j");
            ensuref(b != i, "switch %d cannot affect itself", i);
            ensuref(affected.insert(b).second,
                    "duplicate affected switch %d in list for switch %d", b, i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
