#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for size
    int W = rnd.next(2, 15);
    int H = rnd.next(2, 15);

    // Choose two endpoints (sx,sy) and (ex,ey)
    int sx, sy, ex, ey;
    double alignProb = rnd.next();
    if (alignProb < 0.2) {
        // same row
        sy = rnd.next(0, H-1);
        sx = rnd.next(0, W-1);
        do {
            ex = rnd.next(0, W-1);
        } while (ex == sx);
        ey = sy;
    } else if (alignProb < 0.4) {
        // same column
        sx = rnd.next(0, W-1);
        sy = rnd.next(0, H-1);
        do {
            ey = rnd.next(0, H-1);
        } while (ey == sy);
        ex = sx;
    } else {
        // arbitrary distinct cells
        do {
            sx = rnd.next(0, W-1);
            sy = rnd.next(0, H-1);
            ex = rnd.next(0, W-1);
            ey = rnd.next(0, H-1);
        } while (sx == ex && sy == ey);
    }

    // Build a simple monotonic path from start to end
    vector<char> moves;
    int dx = ex - sx;
    int dy = ey - sy;
    if (dx > 0) for (int i = 0; i < dx; i++) moves.push_back('R');
    if (dx < 0) for (int i = 0; i < -dx; i++) moves.push_back('L');
    if (dy > 0) for (int i = 0; i < dy; i++) moves.push_back('D');
    if (dy < 0) for (int i = 0; i < -dy; i++) moves.push_back('U');
    shuffle(moves.begin(), moves.end());

    vector<pair<int,int>> path;
    path.emplace_back(sx, sy);
    int cx = sx, cy = sy;
    for (char m : moves) {
        if (m == 'R') cx++;
        else if (m == 'L') cx--;
        else if (m == 'D') cy++;
        else if (m == 'U') cy--;
        path.emplace_back(cx, cy);
    }

    // Mark path cells
    vector<vector<bool>> onPath(H, vector<bool>(W, false));
    for (auto &p : path) {
        onPath[p.second][p.first] = true;
    }

    // Initialize grid with walls and empty based on density
    double wallDensity = rnd.next(0.0, 1.0);
    vector<string> grid(H, string(W, '.'));
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (onPath[y][x]) continue;
            // random wall
            if (rnd.next() < wallDensity) grid[y][x] = '*';
        }
    }

    // Place the C endpoints
    grid[sy][sx] = 'C';
    grid[ey][ex] = 'C';

    // Output
    println(W, H);
    for (int y = 0; y < H; y++) {
        println(grid[y]);
    }

    return 0;
}
