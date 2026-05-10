#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the square grid
    int N = inf.readInt(2, 3, "N");
    inf.readEoln();

    // Read the grid
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // Each cell: -1 to 100, but only the bottom-right may be -1
            int x = inf.readInt(-1, 100, "cell");
            if (i == N && j == N) {
                ensuref(x == -1,
                        "Bottom-right cell (row %d, col %d) must be -1, found %d", 
                        i, j, x);
            } else {
                ensuref(x >= 0,
                        "Cell (row %d, col %d) must be between 0 and 100, found %d", 
                        i, j, x);
            }
            if (j < N) {
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
