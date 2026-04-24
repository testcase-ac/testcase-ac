#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter 1: shape of the rectangle
    int shape = rnd.next(1, 3);
    int N, M;
    if (shape == 1) {
        // One row
        N = 1;
        M = rnd.next(3, 20);
    } else if (shape == 2) {
        // One column
        M = 1;
        N = rnd.next(3, 20);
    } else {
        // General small rectangle
        N = rnd.next(2, 5);
        int maxM = 20 / N;
        if (maxM < 2) maxM = 2;
        M = rnd.next(2, maxM);
    }

    // Hyper-parameter 2: fill strategy
    string fillType = rnd.next("random|constant");

    // Build the grid
    vector<string> grid(N, string(M, '0'));
    if (fillType == "constant") {
        // All cells the same non-zero digit
        char c = char('1' + rnd.next(0, 8)); // '1'..'9'
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = c;
    } else {
        // Pure random digits 0..9
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = char('0' + rnd.next(0, 9));
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
