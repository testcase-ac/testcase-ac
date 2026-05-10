#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H, W, X, Y
    int H = inf.readInt(2, 300, "H");
    inf.readSpace();
    int W = inf.readInt(2, 300, "W");
    inf.readSpace();
    int X = inf.readInt(1, H - 1, "X");
    inf.readSpace();
    int Y = inf.readInt(1, W - 1, "Y");
    inf.readEoln();

    int BH = H + X;
    int BW = W + Y;

    vector<vector<int>> B(BH, vector<int>(BW));
    for (int i = 0; i < BH; ++i) {
        B[i] = inf.readInts(BW, 0, 1000, format("B[%d]", i+1));
        inf.readEoln();
    }

    // Check that B is reconstructible to some A (as per problem, always true, but we must check)
    // We'll reconstruct A and check that all A[i][j] in [0,1000]
    vector<vector<int>> A(H, vector<int>(W, 0));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            A[i][j] = B[i][j];
            if (i >= X && j >= Y) {
                A[i][j] -= A[i - X][j - Y];
            }
            ensuref(0 <= A[i][j] && A[i][j] <= 1000,
                "Reconstructed A[%d][%d]=%d is out of bounds [0,1000]", i+1, j+1, A[i][j]);
        }
    }

    // Now, check that reconstructing B from A gives the original B
    vector<vector<int>> B2(BH, vector<int>(BW, 0));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            B2[i][j] += A[i][j];
            if (i + X < BH && j + Y < BW)
                B2[i + X][j + Y] += A[i][j];
        }
    }
    for (int i = 0; i < BH; ++i) {
        for (int j = 0; j < BW; ++j) {
            ensuref(B2[i][j] == B[i][j],
                "B is not consistent with A at (%d,%d): expected %d, got %d",
                i+1, j+1, B[i][j], B2[i][j]);
        }
    }

    inf.readEof();
}
