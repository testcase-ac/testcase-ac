#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        inf.readInt(1, 100, "a_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate position at row %d: %d", i, x);
    }

    inf.readEof();
    return 0;
}
