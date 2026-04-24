#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of rows
    int R = rnd.next(1, 10);

    // Hyper-parameter for number of columns: sometimes small, sometimes moderate
    int C;
    if (rnd.next() < 0.3) {
        C = rnd.next(5, 8);
    } else {
        C = rnd.next(9, 20);
    }

    // Hyper-parameter for building density in interior columns
    double u = rnd.next();
    double density;
    if (u < 0.2) {
        // very sparse
        density = rnd.next() * 0.1;
    } else if (u < 0.4) {
        // very dense
        density = 0.45 + rnd.next() * 0.45;
    } else {
        // moderate
        density = 0.1 + rnd.next() * 0.35;
    }

    // Build the grid
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        // first and last column must be empty
        grid[i][0] = '.';
        grid[i][C-1] = '.';
        // fill interior
        for (int j = 1; j < C-1; j++) {
            if (rnd.next() < density) {
                grid[i][j] = 'x';
            }
        }
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }

    return 0;
}
