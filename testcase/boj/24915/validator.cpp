#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(3, 333333, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 333333, "Q");
    inf.readEoln();

    // Read initial array A[1..N]
    inf.readInts(N, -33333333, 33333333, "A_i");
    inf.readEoln();

    // There must be at least one type-2 query
    bool hasType2 = false;

    // Process Q queries
    for (int i = 0; i < Q; i++) {
        int t = inf.readInt(1, 2, "type_i");
        inf.readSpace();
        if (t == 1) {
            // Update operation: xi yi
            int x = inf.readInt(1, N, "x_i");
            inf.readSpace();
            int y = inf.readInt(-33333333, 33333333, "y_i");
        } else {
            // Query operation: li ri, with li + 2 <= ri
            hasType2 = true;
            int l = inf.readInt(1, N, "l_i");
            inf.readSpace();
            int r = inf.readInt(1, N, "r_i");
            ensuref(l + 2 <= r,
                    "For query %d (type-2): require l+2 <= r, but l=%d, r=%d",
                    i+1, l, r);
        }
        inf.readEoln();
    }

    ensuref(hasType2, "At least one type-2 query must be present");

    inf.readEof();
    return 0;
}
