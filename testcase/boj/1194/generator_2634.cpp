/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);
    // Pick distinct start and exit
    int sx = rnd.next(0, N-1), sy = rnd.next(0, M-1);
    int ex, ey;
    do {
        ex = rnd.next(0, N-1);
        ey = rnd.next(0, M-1);
    } while (ex == sx && ey == sy);
    // Build a Manhattan path from start to exit, then shuffle its steps
    int ddx = ex - sx, ddy = ey - sy;
    vector<pair<int,int>> moves;
    for (int i = 0; i < abs(ddx); i++)
        moves.emplace_back(ddx > 0 ? 1 : -1, 0);
    for (int i = 0; i < abs(ddy); i++)
        moves.emplace_back(0, ddy > 0 ? 1 : -1);
    shuffle(moves.begin(), moves.end());
    // Mark the path cells
    vector<vector<bool>> onPath(N, vector<bool>(M, false));
    int cx = sx, cy = sy;
    onPath[cx][cy] = true;
    for (auto &mv : moves) {
        cx += mv.first;
        cy += mv.second;
        onPath[cx][cy] = true;
    }
    // Initialize grid with walls and carve the path as empty
    vector<string> grid(N, string(M, '#'));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (onPath[i][j])
                grid[i][j] = '.';
    // Place start and exit
    grid[sx][sy] = '0';
    grid[ex][ey] = '1';
    // Randomly turn some non-path cells into empty
    double wallDensity = rnd.next();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!onPath[i][j] && rnd.next() >= wallDensity)
                grid[i][j] = '.';
    // Collect free cells (off-path empties) for keys/doors
    vector<pair<int,int>> freeCells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!onPath[i][j] && grid[i][j] == '.')
                freeCells.emplace_back(i, j);
    shuffle(freeCells.begin(), freeCells.end());
    int available = freeCells.size();
    int ktypesBound = min(available / 3, 2);
    int ktypes = (ktypesBound > 0 ? rnd.next(0, ktypesBound) : 0);
    int idx = 0;
    for (int k = 0; k < ktypes; k++) {
        if (idx >= available) break;
        auto [kx, ky] = freeCells[idx++];
        grid[kx][ky] = char('a' + k);
        int doorCount = rnd.next(1, 2);
        for (int d = 0; d < doorCount && idx < available; d++) {
            auto [dx2, dy2] = freeCells[idx++];
            grid[dx2][dy2] = char('A' + k);
        }
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());
    return 0;
}
