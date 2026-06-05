#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(0, n - 1, "A_i");
        ensuref(!seen[a], "duplicate permutation value at index %d: %d", i, a);
        seen[a] = true;
    }
    inf.readEoln();
    inf.readEof();
}
