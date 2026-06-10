#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int x = inf.readInt(1, 1000, "x_i");
        ensuref(positions.insert(x).second, "duplicate cow position at index %d: %d", i + 1, x);
    }
    inf.readEoln();
    inf.readEof();
}
