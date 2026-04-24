#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // Read the initial array
    inf.readInts(n, 0, 100000, "array");
    inf.readEoln();

    // Read number of queries
    int m = inf.readInt(1, 500000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        // Read query type
        int t = inf.readInt(1, 2, "t");
        if (t == 1) {
            // Type 1: a, b, c
            inf.readSpace();
            int a = inf.readInt(0, n - 1, "a");
            inf.readSpace();
            int b = inf.readInt(0, n - 1, "b");
            inf.readSpace();
            int c = inf.readInt(0, 100000, "c");
            ensuref(a <= b,
                    "Invalid query %d: a (%d) must be <= b (%d)", i, a, b);
        } else {
            // Type 2: a
            inf.readSpace();
            int a = inf.readInt(0, n - 1, "a");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
