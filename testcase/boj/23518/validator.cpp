#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(1, n, "p_i");
        ensuref(!seen[p], "p_i values must form a permutation; duplicate value %d at position %d", p, i);
        seen[p] = 1;

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
