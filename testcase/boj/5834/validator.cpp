#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(-500000, 500000, "P_i");
        inf.readEoln();

        ensuref(p != 0, "P_%d must be nonzero", i);
        ensuref(positions.insert(p).second, "duplicate position at index %d: %d", i, p);
    }

    inf.readEof();
}
