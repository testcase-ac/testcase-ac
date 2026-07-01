#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    for (int row = 1; row <= k; ++row) {
        vector<bool> seen(n + 1, false);
        for (int col = 1; col <= n; ++col) {
            int value = inf.readInt(1, n, "result");
            ensuref(!seen[value],
                    "row %d is not a permutation: value %d appears more than once",
                    row, value);
            seen[value] = true;
            if (col == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
