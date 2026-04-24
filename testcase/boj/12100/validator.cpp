#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    bool hasBlock = false;
    for (int i = 0; i < N; i++) {
        // Read one row of N integers in [0,1024]
        vector<int> row = inf.readInts(N, 0, 1024, "board");
        for (int j = 0; j < N; j++) {
            int v = row[j];
            if (v != 0) {
                hasBlock = true;
                // Non-zero blocks must be >= 2
                ensuref(v >= 2,
                        "board[%d][%d] = %d: block values must be >= 2", 
                        i+1, j+1, v);
                // Must be a power of two
                ensuref((v & (v - 1)) == 0,
                        "board[%d][%d] = %d: block values must be a power of two", 
                        i+1, j+1, v);
            }
        }
        inf.readEoln();
    }

    // There must be at least one non-empty block
    ensuref(hasBlock, "At least one block (value > 0) must be present on the board");

    inf.readEof();
    return 0;
}
