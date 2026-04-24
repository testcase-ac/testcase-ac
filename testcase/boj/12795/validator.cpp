#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of operations
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; i++) {
        // Operation type: 1 = add line, 2 = query
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();

        // The first operation must be of type 1
        if (i == 0) {
            ensuref(t == 1, "The first operation must be type 1, but got %d", t);
        }

        if (t == 1) {
            // Read line parameters a, b
            long long a = inf.readLong(-1000000LL, 1000000LL, "a");
            inf.readSpace();
            long long b = inf.readLong(-1000000000000LL, 1000000000000LL, "b");
            (void)a; (void)b;
        } else {
            // Read query parameter x
            long long x = inf.readLong(-1000000000000LL, 1000000000000LL, "x");
            (void)x;
        }

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
