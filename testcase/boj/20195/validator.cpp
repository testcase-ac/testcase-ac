#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <cassert>
using namespace std;

int dr[4] = {-1, 0, 0, 1}; // N, E, W, S
int dc[4] = {0, 1, -1, 0};
char dirc[4] = {'N', 'E', 'W', 'S'};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(3, 100, "r");
    inf.readSpace();
    int s = inf.readInt(3, 100, "s");
    inf.readEoln();

    vector<string> grid(r);
    int o_cnt = 0, x_cnt = 0;
    int o_r = -1, o_c = -1, x_r = -1, x_c = -1;

    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readLine("[o<>v^.x]{"+to_string(s)+","+to_string(s)+"}", "map row");
        ensuref((int)grid[i].size() == s, "Row %d does not have exactly %d characters", i+1, s);
        for (int j = 0; j < s; ++j) {
            char ch = grid[i][j];
            if (ch == 'o') {
                ++o_cnt;
                o_r = i;
                o_c = j;
            }
            if (ch == 'x') {
                ++x_cnt;
                x_r = i;
                x_c = j;
            }
        }
    }

    // Check exactly one 'o' and one 'x'
    ensuref(o_cnt == 1, "There must be exactly one 'o' on the map, found %d", o_cnt);
    ensuref(x_cnt == 1, "There must be exactly one 'x' on the map, found %d", x_cnt);

    // 'o' must not be on border
    ensuref(o_r > 0 && o_r < r-1 && o_c > 0 && o_c < s-1, "'o' must not be on the border, found at (%d, %d)", o_r+1, o_c+1);

    // Check that all characters are valid (already done by regex, but double check for clarity)
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            char ch = grid[i][j];
            ensuref(
                ch == 'o' || ch == '<' || ch == '>' || ch == 'v' || ch == '^' || ch == '.' || ch == 'x',
                "Invalid character '%c' at (%d, %d)", ch, i+1, j+1
            );
        }
    }

    // Check that all currents never lead outside the map
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            char ch = grid[i][j];
            if (ch == '<') {
                ensuref(j-1 >= 0, "Current '<' at (%d, %d) leads outside map", i+1, j+1);
            }
            if (ch == '>') {
                ensuref(j+1 < s, "Current '>' at (%d, %d) leads outside map", i+1, j+1);
            }
            if (ch == '^') {
                ensuref(i-1 >= 0, "Current '^' at (%d, %d) leads outside map", i+1, j+1);
            }
            if (ch == 'v') {
                ensuref(i+1 < r, "Current 'v' at (%d, %d) leads outside map", i+1, j+1);
            }
        }
    }

    // Check that currents do not form vortexes (no cycles in current graph)
    // Build graph of current cells
    vector<vector<int>> id(r, vector<int>(s, -1));
    int curr_cnt = 0;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < s; ++j)
            if (grid[i][j] == '<' || grid[i][j] == '>' || grid[i][j] == '^' || grid[i][j] == 'v')
                id[i][j] = curr_cnt++;

    vector<vector<int>> adj(curr_cnt);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            int from = id[i][j];
            if (from == -1) continue;
            int ni = i, nj = j;
            if (grid[i][j] == '<') nj--;
            else if (grid[i][j] == '>') nj++;
            else if (grid[i][j] == '^') ni--;
            else if (grid[i][j] == 'v') ni++;
            // If next cell is also a current, add edge
            if (ni >= 0 && ni < r && nj >= 0 && nj < s) {
                int to = id[ni][nj];
                if (to != -1) {
                    adj[from].push_back(to);
                }
            }
        }
    }
    // Detect cycles in the current graph
    vector<int> color(curr_cnt, 0); // 0=unvisited, 1=visiting, 2=visited
    bool has_cycle = false;
    function<void(int)> dfs = [&](int u) {
        color[u] = 1;
        for (int v : adj[u]) {
            if (color[v] == 0) dfs(v);
            else if (color[v] == 1) has_cycle = true;
        }
        color[u] = 2;
    };
    for (int i = 0; i < curr_cnt; ++i) {
        if (color[i] == 0) dfs(i);
    }
    ensuref(!has_cycle, "Currents form a vortex (cycle) in the map");

    inf.readEof();
}
