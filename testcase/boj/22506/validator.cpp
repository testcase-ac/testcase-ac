#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 50, "R");
    inf.readSpace();
    int c = inf.readInt(1, 50, "C");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    vector<string> grid(r);
    int rooms = 0;
    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken("[.#]{1,50}", "layout_row");
        ensuref((int)grid[i].size() == c,
                "layout row %d has length %d, expected %d", i, (int)grid[i].size(), c);
        inf.readEoln();
        for (char ch : grid[i]) {
            rooms += ch == '.';
        }
    }
    ensuref(rooms > 0, "office must contain at least one room");

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    vector<vector<int>> seen(r, vector<int>(c, 0));
    queue<pair<int, int>> q;
    for (int i = 0; i < r && q.empty(); ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == '.') {
                seen[i][j] = 1;
                q.push({i, j});
                break;
            }
        }
    }

    int reached = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        ++reached;
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
                continue;
            }
            if (grid[nx][ny] != '.' || seen[nx][ny]) {
                continue;
            }
            seen[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
    ensuref(reached == rooms, "rooms must be connected, reached %d of %d", reached, rooms);

    int edges = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] != '.') {
                continue;
            }
            if (i + 1 < r && grid[i + 1][j] == '.') {
                ++edges;
            }
            if (j + 1 < c && grid[i][j + 1] == '.') {
                ++edges;
            }
        }
    }
    ensuref(edges == rooms - 1,
            "there must be exactly one route between any pair of rooms: rooms=%d edges=%d",
            rooms, edges);

    for (int matrix = 0; matrix < 3; ++matrix) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                // CHECK: The statement says matrix entries are positive, but official samples
                // use 0 on wall cells. Room cells stay positive; wall cells must be 0.
                int low = grid[i][j] == '.' ? 1 : 0;
                int high = grid[i][j] == '.' ? 1000000000 : 0;
                // CHECK: The statement gives no upper bound for costs; 1e9 is a practical cap.
                inf.readInt(low, high, "cost");
            }
            inf.readEoln();
        }
    }

    for (int i = 0; i < m; ++i) {
        // CHECK: Official samples use zero-based coordinates despite the statement saying
        // positive integers.
        int task_r = inf.readInt(0, r - 1, "task_r");
        inf.readSpace();
        int task_c = inf.readInt(0, c - 1, "task_c");
        inf.readEoln();
        ensuref(grid[task_r][task_c] == '.', "task %d is not on a room: (%d, %d)",
                i + 1, task_r, task_c);
    }

    inf.readEof();
}
