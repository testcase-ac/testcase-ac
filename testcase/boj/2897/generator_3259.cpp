#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small grid dimensions
    int R = rnd.next(2, 10);
    int C = rnd.next(2, 10);

    // Hyper-parameters for diversity: building and car densities
    // buildingMode: 0=no buildings, 1=sparse, 2=moderate
    int buildingMode = rnd.next(0, 2);
    double bldProb;
    if (buildingMode == 0) {
        bldProb = 0.0;
    } else if (buildingMode == 1) {
        bldProb = rnd.next(0.0, 0.2);
    } else {
        bldProb = rnd.next(0.2, 0.5);
    }
    // car density depends inversely on building density
    double carProb = rnd.next(0.0, 1.0 - bldProb);

    // Build the grid
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            double t = rnd.next();
            if (t < bldProb) {
                grid[i][j] = '#';
            } else if (t < bldProb + carProb) {
                grid[i][j] = 'X';
            } else {
                grid[i][j] = '.';
            }
        }
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
