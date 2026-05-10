#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and W
    int H = inf.readInt(1, 500, "H");
    inf.readSpace();
    int W = inf.readInt(1, 500, "W");
    inf.readEoln();

    // Read the grid
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            A[i][j] = inf.readInt(1, 1000000000, "A_i_j");
            if (j + 1 < W) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
