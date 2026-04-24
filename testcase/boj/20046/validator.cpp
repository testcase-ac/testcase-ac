#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    // Product constraint: m * n > 1
    ensuref(1LL * m * n > 1, "Product m * n must be greater than 1, but got %d * %d = %d", 
            m, n, m * n);

    // Read the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int v = inf.readInt(-1, 2, "cell");
            // Explicitly ensure v is one of the allowed values
            ensuref(v == -1 || v == 0 || v == 1 || v == 2,
                    "Invalid cell value at row %d, column %d: %d (allowed: -1,0,1,2)", 
                    i+1, j+1, v);
            if (j + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
