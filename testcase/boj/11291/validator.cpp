#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    set<int> seenX;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 100000, "x");
        inf.readSpace();
        inf.readInt(0, 100000, "y");
        inf.readEoln();

        ensuref(seenX.insert(x).second,
                "duplicate x-coordinate at location %d: %d", i, x);
    }

    inf.readEof();
    return 0;
}
