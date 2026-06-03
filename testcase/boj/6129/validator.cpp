#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<string> field(n);
    int countA = 0;
    int countB = 0;
    pair<int, int> start = {-1, -1};
    pair<int, int> target = {-1, -1};

    for (int i = 0; i < n; ++i) {
        field[i] = inf.readToken("[.xAB]{1,100}", "row");
        inf.readEoln();
        ensuref((int)field[i].size() == n, "row %d has length %d, expected %d", i + 1,
                (int)field[i].size(), n);

        for (int j = 0; j < n; ++j) {
            if (field[i][j] == 'A') {
                ++countA;
                start = {i, j};
            } else if (field[i][j] == 'B') {
                ++countB;
                target = {i, j};
            }
        }
    }

    ensuref(countA == 1, "expected exactly one A, found %d", countA);
    ensuref(countB == 1, "expected exactly one B, found %d", countB);

    vector<vector<int>> seen(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    seen[start.first][start.second] = 1;
    q.push(start);

    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }
            if (seen[nr][nc] || field[nr][nc] == 'x') {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    ensuref(seen[target.first][target.second], "B must be reachable from A");

    inf.readEof();
}
