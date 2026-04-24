#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions: ensure at least 2 cells total
    int m = rnd.next(2, 10);
    int n = rnd.next(2, 10);

    // Hyper-parameters for diversity
    double pX = rnd.next() * 0.3;        // fraction of unbuildable cells
    double p0 = rnd.next() * 0.5;        // fraction of existing roads among buildable
    double p1 = 0.4 + rnd.next() * 0.4;  // within remaining, fraction cost-1 vs cost-2

    // Initialize grid
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Never allow start or end to be unbuildable
            if ((i == 0 && j == 0) || (i == m-1 && j == n-1)) {
                if (rnd.next() < p0) grid[i][j] = 0;
                else grid[i][j] = (rnd.next() < p1 ? 1 : 2);
            } else {
                double r = rnd.next();
                if (r < pX) {
                    grid[i][j] = -1;
                } else if (r < pX + p0) {
                    grid[i][j] = 0;
                } else {
                    grid[i][j] = (rnd.next() < p1 ? 1 : 2);
                }
            }
        }
    }

    // Guarantee at least one buildable path from (0,0) to (m-1,n-1)
    int x = 0, y = 0;
    while (x < m-1 || y < n-1) {
        if (x == m-1) {
            y++;
        } else if (y == n-1) {
            x++;
        } else if (rnd.next() < 0.5) {
            x++;
        } else {
            y++;
        }
        if (grid[x][y] == -1) {
            grid[x][y] = 1;
        }
    }

    // Output
    println(m, n);
    for (int i = 0; i < m; i++) {
        println(grid[i]);
    }

    return 0;
}
