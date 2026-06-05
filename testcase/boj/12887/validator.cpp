#include "testlib.h"

#include <queue>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    vector<string> board(2);
    for (int r = 0; r < 2; ++r) {
        board[r] = inf.readToken("[.#]{1,50}", "row");
        inf.readEoln();
        ensuref((int)board[r].size() == m, "row %d has length %d, expected %d",
                r + 1, (int)board[r].size(), m);
    }

    vector<vector<int>> seen(2, vector<int>(m, 0));
    queue<pair<int, int>> q;
    for (int r = 0; r < 2; ++r) {
        if (board[r][0] == '.') {
            seen[r][0] = 1;
            q.push({r, 0});
        }
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= 2 || nc < 0 || nc >= m) {
                continue;
            }
            if (seen[nr][nc] || board[nr][nc] == '#') {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    bool hasPath = false;
    for (int r = 0; r < 2; ++r) {
        hasPath = hasPath || seen[r][m - 1];
    }
    ensuref(hasPath, "board must contain a white left-to-right path");

    inf.readEof();
}
