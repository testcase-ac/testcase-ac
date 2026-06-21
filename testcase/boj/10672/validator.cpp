#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    set<int> seenY;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000, -1, "x");
        inf.readSpace();
        int y = inf.readInt(1, 1000000, "y");
        inf.readSpace();
        int r = inf.readInt(1, 1000000, "r");
        inf.readEoln();

        ensuref(seenY.insert(y).second,
                "y must be distinct, duplicate y=%d at cow %d", y, i + 1);
    }

    inf.readEof();
}
