#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<int> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        inf.readToken("G|H", "b_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate position at cow %d: %d", i, x);
    }

    inf.readEof();
}
