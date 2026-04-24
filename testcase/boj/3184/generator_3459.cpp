#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int R = rnd.next(3, 20);
    int C = rnd.next(3, 20);
    int fence_pct = rnd.next(0, 30);   // percentage chance of fence in interior
    int occ_pct   = rnd.next(0, 40);   // percentage chance of occupancy (sheep+wolf)
    int sheep_pct = rnd.next(0, 100);  // ratio of sheep within occupied cells

    double fence_prob = fence_pct / 100.0;
    double occ_prob   = occ_pct / 100.0;
    double sheep_frac = sheep_pct / 100.0;
    double sheep_prob = occ_prob * sheep_frac;
    double wolf_prob  = occ_prob * (1.0 - sheep_frac);

    // Build grid with boundary fences to prevent "escape" areas
    vector<string> grid(R, string(C, '.'));
    for (int j = 0; j < C; j++) {
        grid[0][j] = '#';
        grid[R-1][j] = '#';
    }
    for (int i = 0; i < R; i++) {
        grid[i][0] = '#';
        grid[i][C-1] = '#';
    }

    // Fill interior cells
    for (int i = 1; i < R-1; i++) {
        for (int j = 1; j < C-1; j++) {
            double p = rnd.next();
            if (p < fence_prob) {
                grid[i][j] = '#';
            } else if (p < fence_prob + sheep_prob) {
                grid[i][j] = 'o';
            } else if (p < fence_prob + sheep_prob + wolf_prob) {
                grid[i][j] = 'v';
            } else {
                grid[i][j] = '.';
            }
        }
    }

    // Output the test case
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
