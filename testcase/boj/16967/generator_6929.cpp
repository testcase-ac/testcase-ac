#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int H = rnd.next(2, 10);
    int W = rnd.next(2, 10);
    int X = rnd.next(1, H - 1);
    int Y = rnd.next(1, W - 1);

    // Hyper-parameters for A's values
    vector<int> maxChoices = {5, 10, 20, 100};
    int maxA = rnd.any(maxChoices);
    double zeroProb = rnd.next(0.0, 0.7);  // chance to set entry to zero

    // Generate A
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (rnd.next() < zeroProb) {
                A[i][j] = 0;
            } else {
                A[i][j] = rnd.next(1, maxA);
            }
        }
    }

    // Build B by overlaying A and shifted A
    int BH = H + X, BW = W + Y;
    vector<vector<int>> B(BH, vector<int>(BW, 0));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            B[i][j] += A[i][j];
            B[i + X][j + Y] += A[i][j];
        }
    }

    // Output
    println(H, W, X, Y);
    for (int i = 0; i < BH; i++) {
        println(B[i]);
    }
    return 0;
}
