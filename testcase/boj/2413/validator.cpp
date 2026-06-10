#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int value = inf.readInt(1, n, "p_i");
        ensuref(!seen[value], "duplicate permutation value at index %d: %d", i, value);
        seen[value] = true;
    }
    inf.readEoln();
    inf.readEof();
}
