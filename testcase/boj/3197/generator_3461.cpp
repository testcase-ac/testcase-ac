#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int R = rnd.next(2, 10);
    int C = rnd.next(2, 10);
    // Bias parameter for ice density
    vector<int> tvals = {-3, -2, -1, 1, 2, 3};
    int t = rnd.any(tvals);
    double p = rnd.wnext(100, t) / 100.0;  // probability of ice

    // Initialize grid
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < p) grid[i][j] = 'X';
        }
    }

    // Decide placement strategy for swans
    vector<pair<int,int>> swanPos;
    if (rnd.next(0,1) == 0) {
        // anywhere
        vector<pair<int,int>> all;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        swanPos.push_back(all[0]);
        swanPos.push_back(all[1]);
    } else {
        // corners
        vector<pair<int,int>> corners = {{0,0}, {0,C-1}, {R-1,0}, {R-1,C-1}};
        shuffle(corners.begin(), corners.end());
        swanPos.push_back(corners[0]);
        swanPos.push_back(corners[1]);
    }
    // Place swans (override to water)
    for (auto &pr : swanPos) {
        int i = pr.first, j = pr.second;
        grid[i][j] = 'L';
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }
    return 0;
}
