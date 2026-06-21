#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "L");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        int p = inf.readInt(1, 1000000, "P_i");
        inf.readEoln();
        ensuref(positions.insert(p).second,
                "duplicate clump position at index %d: %d", i + 1, p);
    }

    inf.readEof();
}
