#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    // CHECK: the printed bound omits an upper bound for Z, but Z is defined as
    // a field number on the board.
    int z = inf.readInt(2, n, "Z");
    inf.readSpace();
    int m = inf.readInt(0, n - 2, "M");
    inf.readEoln();

    vector<int> obstacles;
    if (m == 0) {
        if (inf.eoln()) {
            // The verifier normalizes trailing blank lines from testcase streams.
        }
        inf.readEof();
        return 0;
    }

    for (int i = 0; i < m; ++i) {
        obstacles.push_back(inf.readInt(1, n, "obstacle"));
        if (i + 1 < m) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    set<int> seen;
    for (int i = 0; i < m; ++i) {
        int field = obstacles[i];
        ensuref(field != 1, "obstacle %d is on start field 1", i + 1);
        ensuref(field != z, "obstacle %d is on goal field Z=%d", i + 1, z);
        ensuref(seen.insert(field).second,
                "duplicate obstacle at index %d: %d",
                i + 1,
                field);
    }

    inf.readEof();
}
