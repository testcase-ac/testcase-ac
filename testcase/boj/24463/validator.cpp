#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2001, "N");
    inf.readSpace();
    int m = inf.readInt(3, 2001, "M");
    inf.readEoln();

    ensuref(n % 2 == 1, "N must be odd: %d", n);
    ensuref(m % 2 == 1, "M must be odd: %d", m);

    vector<string> maze(n);
    vector<pair<int, int>> holes;
    int open_cells = 0;
    for (int i = 0; i < n; ++i) {
        maze[i] = inf.readLine("[.+]{3,2001}", "maze_row");
        ensuref((int)maze[i].size() == m, "row %d length is %d, expected %d", i + 1,
                (int)maze[i].size(), m);
        for (int j = 0; j < m; ++j) {
            if (maze[i][j] != '.') {
                continue;
            }
            ++open_cells;
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                holes.push_back({i, j});
            }
        }
    }

    ensuref((int)holes.size() == 2, "expected exactly 2 boundary holes, found %d",
            (int)holes.size());

    int hole_distance = abs(holes[0].first - holes[1].first) + abs(holes[0].second - holes[1].second);
    ensuref(hole_distance > 1, "the two holes must not be adjacent");

    const int di[4] = {-1, 0, 1, 0};
    const int dj[4] = {0, 1, 0, -1};

    vector<vector<char>> seen(n, vector<char>(m, 0));
    int components = 0;
    bool holes_connected = false;
    long long adjacent_pairs_twice = 0;
    for (int start_i = 0; start_i < n; ++start_i) {
        for (int start_j = 0; start_j < m; ++start_j) {
            if (maze[start_i][start_j] != '.' || seen[start_i][start_j]) {
                continue;
            }

            ++components;
            queue<pair<int, int>> q;
            q.push({start_i, start_j});
            seen[start_i][start_j] = 1;
            bool component_has_first_hole = false;
            bool component_has_second_hole = false;

            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();
                if (i == holes[0].first && j == holes[0].second) {
                    component_has_first_hole = true;
                }
                if (i == holes[1].first && j == holes[1].second) {
                    component_has_second_hole = true;
                }

                for (int dir = 0; dir < 4; ++dir) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= m || maze[ni][nj] != '.') {
                        continue;
                    }
                    ++adjacent_pairs_twice;
                    if (!seen[ni][nj]) {
                        seen[ni][nj] = 1;
                        q.push({ni, nj});
                    }
                }
            }

            if (component_has_first_hole && component_has_second_hole) {
                holes_connected = true;
            }
        }
    }

    ensuref(holes_connected, "the two holes must be connected");

    long long edges = adjacent_pairs_twice / 2;
    ensuref(edges == open_cells - components,
            "path graph must be acyclic: vertices=%d edges=%lld components=%d", open_cells, edges,
            components);

    inf.readEof();
}
