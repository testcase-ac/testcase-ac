#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 0, n - 1, "s_i");
    inf.readEoln();

    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[s[i]], "s_i is not a permutation: duplicate value %d at index %d", s[i], i);
        seen[s[i]] = true;
    }

    int m = inf.readInt(1, 600000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(0, n - 1, "x_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
