#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10, "k");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readEoln();

        ensuref(positions.insert(x).second, "duplicate hay bale position at index %d: %d", i + 1, x);
    }

    inf.readEof();
}
