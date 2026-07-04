#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, n, "x_i");
        ensuref(!seen[x], "x_i values must be distinct, duplicate value %d at position %d", x, i);
        seen[x] = true;

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
