#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int x = inf.readInt(-100000000, 100000000, "x_i");
        ensuref(positions.insert(x).second, "duplicate spring position at index %d: %d", i + 1, x);
    }
    inf.readEoln();
    inf.readEof();
}
