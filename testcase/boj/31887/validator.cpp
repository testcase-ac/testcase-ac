#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2 * n - 2, "M");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, 2 * n - 1, "a_i");
        ensuref(a != n, "a_%d must not be equal to N: %d", i, a);
        ensuref(positions.insert(a).second, "duplicate position at a_%d: %d", i, a);

        if (i < m) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
