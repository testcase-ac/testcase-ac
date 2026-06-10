#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    int k = inf.readInt(m, n, "K");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "x_i");
    inf.readEoln();

    vector<int> starts = inf.readInts(k, 1, n, "rock_position");
    inf.readEoln();
    for (int i = 1; i < k; ++i) {
        ensuref(starts[i - 1] < starts[i],
                "rock positions must be strictly increasing: index %d has %d after %d",
                i + 1, starts[i], starts[i - 1]);
    }

    inf.readEof();
}
