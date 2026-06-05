#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, n, "a_i");
        ensuref(!seen[value], "duplicate card value at position %d: %d", i, value);
        seen[value] = true;

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
