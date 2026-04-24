#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int N = inf.readInt(2, 50, "N");
    inf.readSpace();
    int M = inf.readInt(2, 50, "M");
    inf.readEoln();

    // Read the grid and count zeros and ones
    int cntZero = 0, cntOne = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v = inf.readInt(0, 1, "cell");
            if (v == 0) cntZero++;
            else cntOne++;
            if (j + 1 < M) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Validate at least one empty cell and at least one shark
    ensuref(cntZero > 0, "There must be at least one empty cell (0), found %d", cntZero);
    ensuref(cntOne > 0, "There must be at least one shark cell (1), found %d", cntOne);

    inf.readEof();
    return 0;
}
