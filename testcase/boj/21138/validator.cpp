#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int d = inf.readInt(1, n, "d_i");
        inf.readEoln();

        ensuref(!seen[d], "duplicate height at index %d: %d", i, d);
        seen[d] = true;
    }

    inf.readEof();
}
