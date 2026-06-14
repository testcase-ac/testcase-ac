#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 500, "n");
    inf.readSpace();
    int m = inf.readInt(4, 500, "m");
    inf.readEoln();

    vector<string> board(n);
    int detective_count = 0;
    int robber_count = 0;
    pair<int, int> start = {-1, -1};

    for (int i = 0; i < n; ++i) {
        board[i] = inf.readLine("[#\\.DR]{4,500}", "row");
        ensuref((int)board[i].size() == m,
                "row %d has length %d, expected %d", i + 1,
                (int)board[i].size(), m);

        for (int j = 0; j < m; ++j) {
            char cell = board[i][j];
            if (cell == 'D') {
                ++detective_count;
            } else if (cell == 'R') {
                ++robber_count;
            }

            if (cell != '#' && start.first == -1) {
                start = {i, j};
            }
        }
    }

    ensuref(detective_count == 1, "expected exactly one D, found %d",
            detective_count);
    ensuref(robber_count == 1, "expected exactly one R, found %d",
            robber_count);

    for (int i = 0; i < n; ++i) {
        ensuref(board[i][0] == '#', "left border cell (%d, 1) is not a wall",
                i + 1);
        ensuref(board[i][m - 1] == '#',
                "right border cell (%d, %d) is not a wall", i + 1, m);
    }
    for (int j = 0; j < m; ++j) {
        ensuref(board[0][j] == '#', "top border cell (1, %d) is not a wall",
                j + 1);
        ensuref(board[n - 1][j] == '#',
                "bottom border cell (%d, %d) is not a wall", n, j + 1);
    }

    vector<vector<int>> seen(n, vector<int>(m, 0));
    queue<pair<int, int>> q;
    q.push(start);
    seen[start.first][start.second] = 1;

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }
            if (board[nr][nc] == '#' || seen[nr][nc]) {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ensuref(board[i][j] == '#' || seen[i][j],
                    "non-wall cell (%d, %d) is not connected", i + 1, j + 1);
        }
    }

    inf.readEof();
}
