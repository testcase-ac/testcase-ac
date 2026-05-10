#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of matrices
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Read matrix dimensions and validate chain multiplication feasibility
    int prev_c = -1;
    for (int i = 0; i < N; i++) {
        // Read r_i and c_i
        int r = inf.readInt(1, 500, "r");
        inf.readSpace();
        int c = inf.readInt(1, 500, "c");
        inf.readEoln();

        if (i > 0) {
            // Check that previous matrix's column count equals this matrix's row count
            ensuref(prev_c == r,
                    "Dimension mismatch between matrix %d (%d x %d) and matrix %d (%d x %d)",
                    i,                 // previous matrix index (1-based)
                    /*prev_r placeholder*/ -1, prev_c, // prev_r is not needed here
                    i+1,               // current matrix index
                    r, c);
        }
        prev_c = c;
    }

    inf.readEof();
    return 0;
}
