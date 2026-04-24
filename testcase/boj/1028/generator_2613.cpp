/* generator code */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);

    // Initialize grid with random noise
    vector<string> grid(R, string(C, '0'));
    double fillProb = rnd.next(); // probability for a 1
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < fillProb) {
                grid[i][j] = '1';
            }
        }
    }

    // Embed at least one diamond of random size S >= 1
    int maxS = min((R + 1) / 2, (C + 1) / 2);
    int S = rnd.next(1, maxS);
    int radius = S - 1;

    // Choose a valid center so the diamond fits
    int ci = rnd.next(radius, R - 1 - radius);
    int cj = rnd.next(radius, C - 1 - radius);

    // Draw the boundary of the diamond: |dx| + |dy| == radius
    for (int dx = -radius; dx <= radius; dx++) {
        int dy = radius - abs(dx);
        grid[ci + dx][cj + dy] = '1';
        grid[ci + dx][cj - dy] = '1';
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }

    return 0;
}
