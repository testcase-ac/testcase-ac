#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Point {
    int x, y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_W = 20;
    const int MAX_H = 20;
    const int MAX_DIRTY = 10;

    while (true) {
        int w = inf.readInt(0, MAX_W, "w");
        inf.readSpace();
        int h = inf.readInt(0, MAX_H, "h");
        inf.readEoln();

        if (w == 0 && h == 0) break;

        // w,h must both be >=1 for real testcases (last line is only 0 0)
        ensuref(w >= 1 && h >= 1, "For non-final testcases, 1 <= w,h <= 20 must hold");

        vector<string> grid(h);
        int robotCount = 0;
        int dirtyCount = 0;
        Point robot;
        vector<Point> dirts;

        for (int i = 0; i < h; ++i) {
            grid[i] = inf.readLine("[^]{1,20}", "row");
            ensuref((int)grid[i].size() == w,
                    "Row %d length must be exactly w=%d, but is %d", i, w, (int)grid[i].size());

            for (int j = 0; j < w; ++j) {
                char c = grid[i][j];
                ensuref(c == '.' || c == '*' || c == 'x' || c == 'o',
                        "Invalid character '%c' at row %d, col %d", c, i, j);

                if (c == 'o') {
                    robotCount++;
                    robot = {j, i};
                } else if (c == '*') {
                    dirtyCount++;
                    ensuref(dirtyCount <= MAX_DIRTY,
                            "Number of dirty cells exceeds %d", MAX_DIRTY);
                    dirts.push_back({j, i});
                }
            }
        }

        ensuref(robotCount == 1, "There must be exactly one robot, found %d", robotCount);

        // Connectivity / reachability check: all dirty cells must be reachable from robot,
        // otherwise output is -1 per statement, but we must ensure input respects
        // the *guarantee* if there was any. Here, statement says output can be -1,
        // so non-reachability is allowed; we do NOT reject such inputs.
        // However, we must still ensure that movement rules are coherent:
        // simulate BFS just to check we don't rely on any unstated guarantee.
        // No additional ensuref based on reachability is needed.

        // BFS reachability simulation (no constraints enforced from it)
        auto inBounds = [&](int x, int y) {
            return x >= 0 && x < w && y >= 0 && y < h;
        };
        vector<vector<int>> dist(h, vector<int>(w, -1));
        queue<Point> q;
        dist[robot.y][robot.x] = 0;
        q.push(robot);
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            Point p = q.front(); q.pop();
            for (int dir = 0; dir < 4; ++dir) {
                int nx = p.x + dx[dir];
                int ny = p.y + dy[dir];
                if (!inBounds(nx, ny)) continue;
                if (grid[ny][nx] == 'x') continue;
                if (dist[ny][nx] != -1) continue;
                dist[ny][nx] = dist[p.y][p.x] + 1;
                q.push({nx, ny});
            }
        }
        // We don't enforce reachability; it's part of the problem's solution.

        // End of one test case
    }

    inf.readEof();
}
