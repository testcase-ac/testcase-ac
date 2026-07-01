#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 13, "n");
    inf.readEoln();

    vector<int> seen(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(0, n - 1, "p_i");
        ensuref(!seen[value], "duplicate permutation value at position %d: %d", i + 1, value);
        seen[value] = 1;
    }
    inf.readEoln();
    inf.readEof();
}
