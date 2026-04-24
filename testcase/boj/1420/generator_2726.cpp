#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for size
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);
    // List all cells
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());
    // Choose positions for K and H
    auto [kx, ky] = cells[0];
    auto [hx, hy] = cells[1];
    // Hyper-parameters for wall density bias
    int wParam = rnd.next(-2, 2);           // bias parameter
    int threshold = rnd.next(10, 90);       // wall threshold out of 100
    // Whether to carve a guaranteed simple path
    bool carvePath = rnd.next(0, 1) == 1;
    // Initialize grid with empty
    vector<string> grid(N, string(M, '.'));
    // Randomly assign walls (avoid K/H)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i == kx && j == ky) || (i == hx && j == hy)) continue;
            int wv = rnd.wnext(100, wParam);
            if (wv < threshold) grid[i][j] = '#';
        }
    }
    // Optionally carve a direct path from K to H
    if (carvePath) {
        int cx = kx, cy = ky;
        while (cx != hx || cy != hy) {
            if (cx != hx && cy != hy) {
                if (rnd.next(0,1)) cx += (hx > cx ? 1 : -1);
                else           cy += (hy > cy ? 1 : -1);
            } else if (cx != hx) {
                cx += (hx > cx ? 1 : -1);
            } else {
                cy += (hy > cy ? 1 : -1);
            }
            if (!(cx == kx && cy == ky)) // keep path cells open
                grid[cx][cy] = '.';
        }
    }
    // Place K and H
    grid[kx][ky] = 'K';
    grid[hx][hy] = 'H';
    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(grid[i]);
    return 0;
}
