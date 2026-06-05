#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 500, "H");
    inf.readSpace();
    int w = inf.readInt(1, 500, "W");
    inf.readEoln();

    vector<string> grid(h);
    pair<int, int> start = {-1, -1};
    pair<int, int> finish = {-1, -1};
    int start_count = 0;
    int finish_count = 0;

    string row_pattern = "[.#SE]{" + to_string(w) + "," + to_string(w) + "}";
    for (int i = 0; i < h; ++i) {
        grid[i] = inf.readLine(row_pattern, "row");
        for (int j = 0; j < w; ++j) {
            char cell = grid[i][j];
            if (cell == 'S') {
                ++start_count;
                start = {i, j};
            } else if (cell == 'E') {
                ++finish_count;
                finish = {i, j};
            }

            if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
                ensuref(cell == '#', "border cell (%d, %d) must be wall", i + 1, j + 1);
            }
        }
    }

    ensuref(start_count == 1, "expected exactly one S, found %d", start_count);
    ensuref(finish_count == 1, "expected exactly one E, found %d", finish_count);

    vector<vector<int>> seen(h, vector<int>(w, 0));
    queue<pair<int, int>> q;
    seen[start.first][start.second] = 1;
    q.push(start);

    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int ni = i + di[d];
            int nj = j + dj[d];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) {
                continue;
            }
            if (seen[ni][nj] || grid[ni][nj] == '#') {
                continue;
            }
            seen[ni][nj] = 1;
            q.push({ni, nj});
        }
    }

    ensuref(seen[finish.first][finish.second], "E must be reachable from S through non-wall cells");

    inf.readEof();
}
