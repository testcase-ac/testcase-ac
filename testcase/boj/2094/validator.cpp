#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of known years
    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    vector<int> years(n);
    for (int i = 0; i < n; i++) {
        int y = inf.readInt(-1000000000, 1000000000, "y_i");
        inf.readSpace();
        int r = inf.readInt(1, 1000000000, "r_i");
        inf.readEoln();

        years[i] = y;
        if (i > 0) {
            ensuref(years[i] > years[i-1],
                    "Years must be strictly increasing: y[%d]=%d <= y[%d]=%d",
                    i, years[i], i-1, years[i-1]);
        }
    }

    // Read number of queries
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int Y = inf.readInt(-1000000000, 1000000000, "Y_i");
        inf.readSpace();
        int X = inf.readInt(-1000000000, 1000000000, "X_i");
        inf.readEoln();

        ensuref(Y < X,
                "In query %d: Y (%d) must be less than X (%d)", 
                i, Y, X);
    }

    inf.readEof();
    return 0;
}
