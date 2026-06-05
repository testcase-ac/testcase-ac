#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 2 * rnd.next(1, 9) + 1;
    int m = 2 * rnd.next(1, 9) + 1;
    vector<string> maze(n, string(m, '+'));

    const int di[4] = {-1, 0, 1, 0};
    const int dj[4] = {0, 1, 0, -1};

    vector<pair<int, int>> frontier;
    auto open_cell = [&](int i, int j) {
        if (maze[i][j] == '.') {
            return;
        }
        maze[i][j] = '.';
        if (i > 0 && i + 1 < n && j > 0 && j + 1 < m) {
            frontier.push_back({i, j});
        }
    };

    if (rnd.next(2) == 0) {
        int row = rnd.next(1, n - 2);
        for (int j = 0; j < m; ++j) {
            open_cell(row, j);
        }
    } else {
        int col = rnd.next(1, m - 2);
        for (int i = 0; i < n; ++i) {
            open_cell(i, col);
        }
    }

    double branch_probability = rnd.next(0.15, 0.90);
    int base_path_cells = min(n, m);
    int max_target_open_cells = max(base_path_cells, n * m / rnd.next(3, 7));
    int target_open_cells = rnd.next(base_path_cells, max_target_open_cells);

    for (int cursor = 0; cursor < (int)frontier.size(); ++cursor) {
        int pick = rnd.next(cursor, (int)frontier.size() - 1);
        swap(frontier[cursor], frontier[pick]);
        auto [i, j] = frontier[cursor];

        vector<pair<int, int>> candidates;
        for (int dir = 0; dir < 4; ++dir) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            if (ni <= 0 || ni + 1 >= n || nj <= 0 || nj + 1 >= m || maze[ni][nj] == '.') {
                continue;
            }

            int open_neighbors = 0;
            for (int ndir = 0; ndir < 4; ++ndir) {
                int ai = ni + di[ndir];
                int aj = nj + dj[ndir];
                if (maze[ai][aj] == '.') {
                    ++open_neighbors;
                }
            }
            if (open_neighbors == 1) {
                candidates.push_back({ni, nj});
            }
        }

        shuffle(candidates.begin(), candidates.end());
        for (auto [ni, nj] : candidates) {
            if ((int)frontier.size() >= target_open_cells || rnd.next() > branch_probability) {
                continue;
            }
            open_cell(ni, nj);
        }
    }

    println(n, m);
    for (const string& row : maze) {
        println(row);
    }
}
