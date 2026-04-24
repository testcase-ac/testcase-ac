#include "testlib.h"
using namespace std;

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample dimensions ensuring at least one island survives after 50 years
    int R, C;
    do {
        R = rnd.next(1, 10);
        C = rnd.next(1, 10);
    } while (!((R >= 2 && C >= 2) || (R == 1 && C >= 3) || (C == 1 && R >= 3)));

    // Hyper-parameters for density and bias
    vector<int> ts = {-1, 1};
    int t = rnd.any(ts);
    int densInt = rnd.wnext(9, t) + 1; // 1..10
    double dens = densInt / 10.0;
    bool borderBias = rnd.next(0, 1) == 1;

    vector<string> grid(R, string(C, '.'));
    int maxDist = (min(R, C) - 1) / 2;

    // Fill grid with random land based on density and bias
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            double base = dens;
            int d = min(min(i, R - 1 - i), min(j, C - 1 - j));
            if (borderBias) {
                base *= (1.0 - double(d) / (maxDist + 1));
            } else {
                base *= (0.5 + double(d) / (2.0 * (maxDist + 1)));
            }
            if (rnd.next() < base) {
                grid[i][j] = 'X';
            }
        }
    }

    // Force a guaranteed surviving shape after 50 years
    if (R >= 2 && C >= 2) {
        // 2x2 block
        int i0 = rnd.next(0, R - 2);
        int j0 = rnd.next(0, C - 2);
        grid[i0][j0] = 'X';
        grid[i0 + 1][j0] = 'X';
        grid[i0][j0 + 1] = 'X';
        grid[i0 + 1][j0 + 1] = 'X';
    } else if (R == 1) {
        // 1xC, C>=3: place a horizontal length-3 segment
        int j0 = rnd.next(0, C - 3);
        for (int k = 0; k < 3; k++) {
            grid[0][j0 + k] = 'X';
        }
    } else {
        // C==1, R>=3: vertical length-3 segment
        int i0 = rnd.next(0, R - 3);
        for (int k = 0; k < 3; k++) {
            grid[i0 + k][0] = 'X';
        }
    }

    // Output the generated test case
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
