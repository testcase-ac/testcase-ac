#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose grid size with variability, sometimes 1D
    int N, M;
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        N = 1;
        M = rnd.next(2, 20);
    } else if (mode == 1) {
        N = rnd.next(2, 20);
        M = 1;
    } else {
        N = rnd.wnext(19, 2) + 1;
        M = rnd.wnext(19, 2) + 1;
        if (N < 2) N = 2;
        if (M < 2) M = 2;
    }
    // Prepare grid
    vector<string> grid(N, string(M, '.'));
    // Determine positions for A and B, with corner bias
    vector<pair<int,int>> corners;
    corners.push_back({0,0});
    if (M > 1) corners.push_back({0, M-1});
    if (N > 1) corners.push_back({N-1, 0});
    if (N > 1 && M > 1) corners.push_back({N-1, M-1});
    pair<int,int> posA, posB;
    if ((int)corners.size() >= 2 && rnd.next(0,3) == 0) {
        int ai = rnd.next(0, (int)corners.size() - 1);
        int bi = rnd.next(0, (int)corners.size() - 2);
        if (bi >= ai) bi++;
        posA = corners[ai];
        posB = corners[bi];
    } else {
        vector<pair<int,int>> cells;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end());
        posA = cells[0];
        posB = cells[1];
    }
    grid[posA.first][posA.second] = 'A';
    grid[posB.first][posB.second] = 'B';
    // Obstacle density hyper-parameter
    int d;
    int dd = rnd.next(0,3);
    if (dd == 0) {
        d = rnd.wnext(100, -1); // low density
    } else if (dd == 1) {
        d = rnd.wnext(100, 2);  // high density
    } else {
        d = rnd.next(0, 100);   // uniform
    }
    // Fill obstacles
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') {
                if (rnd.next(100) < d) grid[i][j] = 'X';
            }
        }
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) println(grid[i]);
    return 0;
}
