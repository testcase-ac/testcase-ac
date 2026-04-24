#include "testlib.h"
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

const int MAX_W = 100;
const int MAX_H = 100;

int dx[4] = {0, 1, 0, -1}; // up, right, down, left
int dy[4] = {-1, 0, 1, 0};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int W = inf.readInt(1, MAX_W, "W");
    inf.readSpace();
    int H = inf.readInt(1, MAX_H, "H");
    inf.readEoln();

    vector<string> grid(H);
    int c_count = 0;
    vector<pair<int,int>> c_pos;

    for (int i = 0; i < H; ++i) {
        grid[i] = inf.readLine("[.*C]{"+to_string(W)+","+to_string(W)+"}", "map row");
        ensuref((int)grid[i].size() == W, "Row %d: length is %d, expected %d", i+1, (int)grid[i].size(), W);
        for (int j = 0; j < W; ++j) {
            char ch = grid[i][j];
            ensuref(ch == '.' || ch == '*' || ch == 'C', "Row %d, Col %d: invalid character '%c'", i+1, j+1, ch);
            if (ch == 'C') {
                ++c_count;
                c_pos.emplace_back(i, j);
            }
        }
    }
    ensuref(c_count == 2, "There must be exactly two 'C' cells, found %d", c_count);

    // Check that the two 'C' are at different positions
    ensuref(!(c_pos[0] == c_pos[1]), "'C' cells must be at different positions");

    // Now, check that the two 'C' can be connected by laser (i.e., there is a path from c_pos[0] to c_pos[1] using only '.', 'C', and mirrors)
    // Since the problem guarantees this, we must check it.

    // 0: up, 1: right, 2: down, 3: left
    // For each cell and direction, store minimal mirrors used to reach there
    int dist[MAX_H][MAX_W][4];
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            for (int d = 0; d < 4; ++d)
                dist[i][j][d] = -1;

    int sx = c_pos[0].second, sy = c_pos[0].first;
    int ex = c_pos[1].second, ey = c_pos[1].first;

    deque<tuple<int,int,int,int>> q; // (y, x, dir, mirrors)
    // Start from all 4 directions from the first 'C'
    for (int d = 0; d < 4; ++d) {
        int nx = sx + dx[d], ny = sy + dy[d];
        if (0 <= nx && nx < W && 0 <= ny && ny < H && grid[ny][nx] != '*') {
            dist[sy][sx][d] = 0;
            q.emplace_back(sy, sx, d, 0);
        }
    }

    while (!q.empty()) {
        int y, x, dir, mirrors;
        tie(y, x, dir, mirrors) = q.front();
        q.pop_front();

        // Move forward in the same direction
        int nx = x + dx[dir], ny = y + dy[dir];
        if (0 <= nx && nx < W && 0 <= ny && ny < H && grid[ny][nx] != '*') {
            if (dist[ny][nx][dir] == -1 || dist[ny][nx][dir] > mirrors) {
                dist[ny][nx][dir] = mirrors;
                q.emplace_front(ny, nx, dir, mirrors); // 0-1 BFS: no mirror, so push front
            }
        }
        // Try to turn (place a mirror)
        for (int nd = 0; nd < 4; ++nd) {
            if (nd == dir) continue;
            if ((dir + 2) % 4 == nd) continue; // cannot turn 180 degrees
            if (dist[y][x][nd] == -1 || dist[y][x][nd] > mirrors + 1) {
                dist[y][x][nd] = mirrors + 1;
                q.emplace_back(y, x, nd, mirrors + 1); // push back, as it costs a mirror
            }
        }
    }

    // Check if the second 'C' is reachable
    bool reachable = false;
    for (int d = 0; d < 4; ++d) {
        if (dist[ey][ex][d] != -1) {
            reachable = true;
            break;
        }
    }
    ensuref(reachable, "The two 'C' cells are not connectable by laser (contradicts problem guarantee)");

    inf.readEof();
}
