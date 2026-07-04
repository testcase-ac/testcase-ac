#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 1000, "R");
    inf.readSpace();
    int c = inf.readInt(2, 1000, "C");
    inf.readEoln();

    vector<string> grid(r);
    vector<pair<int, int>> turtle;
    int homeCount = 0;
    int obstacleCount = 0;

    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken(format("[HT#.]{%d}", c).c_str(), "row");
        inf.readEoln();

        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == 'H') {
                ++homeCount;
            } else if (grid[i][j] == 'T') {
                turtle.push_back({i, j});
            } else if (grid[i][j] == '#') {
                ++obstacleCount;
            }
        }
    }

    ensuref(homeCount == 1, "expected exactly one H, found %d", homeCount);
    ensuref(!turtle.empty(), "expected at least one T cell");
    ensuref(obstacleCount <= 20, "expected at most 20 obstacles, found %d", obstacleCount);

    vector<vector<int>> seen(r, vector<int>(c, 0));
    queue<pair<int, int>> q;
    q.push(turtle[0]);
    seen[turtle[0].first][turtle[0].second] = 1;

    int reached = 0;
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        ++reached;

        for (int dir = 0; dir < 4; ++dir) {
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                continue;
            }
            if (seen[nr][nc] || grid[nr][nc] != 'T') {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    ensuref(reached == (int)turtle.size(),
            "T cells must form one 4-connected component, reached %d of %d",
            reached, (int)turtle.size());

    inf.readEof();
}
