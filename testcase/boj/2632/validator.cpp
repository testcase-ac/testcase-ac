#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Target pizza size T: a natural number up to 2,000,000
    int T = inf.readInt(1, 2000000, "T");
    inf.readEoln();

    // m and n: number of slices in pizza A and B, each between 3 and 1000
    int m = inf.readInt(3, 1000, "m");
    inf.readSpace();
    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    // Read m lines for pizza A slice sizes
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, 1000, "A_i");
        inf.readEoln();
    }

    // Read n lines for pizza B slice sizes
    for (int i = 0; i < n; i++) {
        int b = inf.readInt(1, 1000, "B_i");
        inf.readEoln();
    }

    // No further content allowed
    inf.readEof();
    return 0;
}
