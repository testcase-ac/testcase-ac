#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    // Read the grid: n rows of m entries (0 or 1), space-separated
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inf.readInt(0, 1, "cell");
            if (j + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
