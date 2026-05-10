#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "k");
    inf.readEoln();

    // Read the grid
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = inf.readInt(-1, 1000000, "a");
            if (j < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // If not obstacle, must be at least 1
            ensuref(x == -1 || x >= 1,
                    "Cell a[%d][%d] must be -1 or in [1,1e6], found %d", i, j, x);
            // Starting cell must not be an obstacle
            if (i == 1 && j == 1) {
                ensuref(x != -1,
                        "Starting cell (1,1) must not contain an obstacle");
            }
        }
    }

    inf.readEof();
    return 0;
}
