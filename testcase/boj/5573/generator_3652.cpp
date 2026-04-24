#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small dimensions
    int H = rnd.next(1, 10);
    int W = rnd.next(1, 10);

    // Hyper-parameter for grid density
    double density = rnd.next(); // in [0,1)
    vector<vector<int>> grid(H, vector<int>(W));

    // Some special patterns
    double mode = rnd.next();
    if (mode < 0.2) {
        // all zeros
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                grid[i][j] = 0;
    } else if (mode < 0.4) {
        // all ones
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                grid[i][j] = 1;
    } else if (mode < 0.6) {
        // checkerboard
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                grid[i][j] = (i + j) % 2;
    } else {
        // random by density
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                grid[i][j] = (rnd.next() < density) ? 1 : 0;
    }

    // Hyper-parameter for N selection
    int Nmax;
    double pick = rnd.next();
    if (pick < 0.3) {
        Nmax = 1;
    } else if (pick < 0.6) {
        Nmax = H * W;
    } else if (pick < 0.9) {
        Nmax = H * W * 2;
    } else {
        Nmax = H * W * 5;
    }
    if (Nmax < 1) Nmax = 1;
    int N = rnd.next(1, Nmax);

    // Output
    println(H, W, N);
    for (int i = 0; i < H; i++)
        println(grid[i]);

    return 0;
}
