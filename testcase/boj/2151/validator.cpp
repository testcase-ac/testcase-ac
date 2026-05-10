#include "testlib.h"
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct State {
    int x, y, d;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 50;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    vector<string> grid(N);
    int doorCount = 0;
    pair<int,int> doors[2];

    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readLine("[#.!*]{1,50}", "row");
        ensuref((int)grid[i].size() == N,
                "Row %d must have exactly %d characters, got %d",
                i, N, (int)grid[i].size());
        for (int j = 0; j < N; ++j) {
            char c = grid[i][j];
            ensuref(c == '#' || c == '.' || c == '!' || c == '*',
                    "Invalid character '%c' at (%d, %d)", c, i, j);
            if (c == '#') {
                ensuref(doorCount < 2,
                        "More than two doors ('#') found, extra at (%d, %d)", i, j);
                doors[doorCount++] = {i, j};
            }
        }
    }

    ensuref(doorCount == 2, "There must be exactly two doors ('#'), found %d", doorCount);

    // Global property: "거울을 어떻게 설치해도 한 쪽 문에서 다른 쪽 문을 볼 수 없는 경우는 주어지지 않는다."
    // i.e., there always exists some way (with mirrors on '!' positions) to connect the two doors with light.
    // Validate by actually computing minimum mirrors using 0-1 BFS and ensuring reachability.

    int sx = doors[0].first, sy = doors[0].second;
    int tx = doors[1].first, ty = doors[1].second;

    const int INF = 1e9;
    // directions: 0 = up, 1 = right, 2 = down, 3 = left
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    // dist[x][y][d] = min mirrors to reach (x,y) coming from direction d
    vector<vector<array<int,4>>> dist(N, vector<array<int,4>>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int d = 0; d < 4; ++d)
                dist[i][j][d] = INF;

    deque<State> dq;

    // From starting door, we can emit light in all four directions without cost
    for (int d = 0; d < 4; ++d) {
        dist[sx][sy][d] = 0;
        dq.push_back({sx, sy, d});
    }

    auto inBounds = [&](int x, int y) {
        return 0 <= x && x < N && 0 <= y && y < N;
    };

    while (!dq.empty()) {
        State cur = dq.front();
        dq.pop_front();
        int x = cur.x, y = cur.y, d = cur.d;
        int curCost = dist[x][y][d];
        if (curCost == INF) continue;

        int nx = x + dx[d];
        int ny = y + dy[d];

        if (!inBounds(nx, ny)) continue;
        char cell = grid[nx][ny];
        if (cell == '*') continue;

        // Move straight
        if (dist[nx][ny][d] > curCost) {
            dist[nx][ny][d] = curCost;
            dq.push_front({nx, ny, d});
        }

        // If we can place a mirror at '!' or are at a door '#', we may change direction.
        if (cell == '!' || cell == '#') {
            // mirror types allow turning 90 degrees: from (up/down) to (left/right) and vice versa
            // We try both possible turns
            for (int nd = 0; nd < 4; ++nd) {
                if (nd == d) continue;
                // Only 90-degree turns
                if ((d % 2) == (nd % 2)) continue;
                int ncost = curCost + 1;
                if (dist[nx][ny][nd] > ncost) {
                    dist[nx][ny][nd] = ncost;
                    dq.push_back({nx, ny, nd});
                }
            }
        }
    }

    int best = INF;
    for (int d = 0; d < 4; ++d)
        best = min(best, dist[tx][ty][d]);

    ensuref(best < INF,
            "No valid light path between doors at (%d,%d) and (%d,%d)",
            sx, sy, tx, ty);

    inf.readEof();
}
