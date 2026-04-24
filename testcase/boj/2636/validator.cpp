#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read grid rows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cell = inf.readInt(0, 1, "A[i][j]");
            // Check border cells are zero
            if (i == 0 || i == N-1 || j == 0 || j == M-1) {
                ensuref(cell == 0,
                        "Border cell at (%d,%d) must be 0 but found %d", 
                        i, j, cell);
            }
            if (j < M-1) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
