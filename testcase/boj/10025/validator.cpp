#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 2000000, "K");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 10000, "g_i");
        inf.readSpace();
        int x = inf.readInt(0, 1000000, "x_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate bucket position at line %d: %d", i + 2, x);
    }

    inf.readEof();
    return 0;
}
