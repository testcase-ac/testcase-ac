#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int c = inf.readInt(1, 100000000, "c");
    inf.readEoln();

    vector<int> weights = inf.readInts(n, 1, 100000000, "w_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(weights[i]).second,
                "duplicate weight at index %d: %d", i + 1, weights[i]);
    }

    inf.readEof();
}
