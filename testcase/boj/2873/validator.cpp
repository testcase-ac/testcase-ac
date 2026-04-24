#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int R = inf.readInt(2, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(2, 1000, "C");
    inf.readEoln();

    // Read the joy values for each cell
    // Each must be a positive integer less than 1000, i.e., in [1, 999].
    for (int i = 0; i < R; i++) {
        vector<int> row = inf.readInts(C, 1, 999, "joy");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
