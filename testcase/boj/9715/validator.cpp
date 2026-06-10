#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalCells = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int r = inf.readInt(1, 50, "R");
        inf.readSpace();
        int c = inf.readInt(1, 50, "C");
        inf.readEoln();

        totalCells += r * c;
        // CHECK: T has no statement bound; cap cumulative grid size near the
        // local string-input limit while still allowing many small cases.
        ensuref(totalCells <= 10000000,
                "total grid cells exceed practical cap: %d", totalCells);

        vector<string> grid(r);
        vector<vector<int>> seen(r, vector<int>(c, 0));
        pair<int, int> start = {-1, -1};
        int positiveCells = 0;

        for (int i = 0; i < r; ++i) {
            grid[i] = inf.readToken("[0-9]{" + to_string(c) + "}", "row");
            inf.readEoln();

            for (int j = 0; j < c; ++j) {
                if (grid[i][j] != '0') {
                    ++positiveCells;
                    if (start.first == -1) {
                        start = {i, j};
                    }
                }
            }
        }

        ensuref(positiveCells > 0, "case has no columns");

        queue<pair<int, int>> q;
        q.push(start);
        seen[start.first][start.second] = 1;
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
                if (seen[nr][nc] || grid[nr][nc] == '0') {
                    continue;
                }
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }

        ensuref(reached == positiveCells,
                "positive columns are not 4-neighbor connected: reached %d of %d",
                reached, positiveCells);
    }

    inf.readEof();
}
