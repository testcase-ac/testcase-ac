#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read block dimensions
    int h = inf.readInt(1, 100, "h");
    inf.readSpace();
    int w = inf.readInt(1, 100, "w");
    inf.readEoln();

    // Read the block grid
    vector<string> grid(h);
    string row_regex = string("[#.]{") + to_string(w) + "," + to_string(w) + "}";
    for (int i = 0; i < h; i++) {
        grid[i] = inf.readLine(row_regex, "row");
    }

    // Count filled cells and find a start for BFS
    int total_hash = 0;
    int start_r = -1, start_c = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') {
                total_hash++;
                if (start_r < 0) {
                    start_r = i;
                    start_c = j;
                }
            }
        }
    }
    ensuref(total_hash > 0, "The block must have at least one '#'");

    // Check connectivity via BFS
    vector<vector<bool>> seen(h, vector<bool>(w, false));
    queue<pair<int,int>> q;
    q.push({start_r, start_c});
    seen[start_r][start_c] = true;
    int reachable = 0;
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (grid[r][c] == '#') {
            reachable++;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < h && nc >= 0 && nc < w
                    && !seen[nr][nc] && grid[nr][nc] == '#') {
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    ensuref(reachable == total_hash,
            "The '#' cells must form exactly one orthogonally connected component; found %d reachable of %d",
            reachable, total_hash);

    // Ensure the block exactly fits its bounding box:
    // first and last row, first and last column each contain at least one '#'
    bool first_row_has = false, last_row_has = false;
    for (int j = 0; j < w; j++) {
        if (grid[0][j] == '#') first_row_has = true;
        if (grid[h-1][j] == '#') last_row_has = true;
    }
    ensuref(first_row_has, "The first row must contain at least one '#'");
    ensuref(last_row_has, "The last row must contain at least one '#'");

    bool first_col_has = false, last_col_has = false;
    for (int i = 0; i < h; i++) {
        if (grid[i][0] == '#') first_col_has = true;
        if (grid[i][w-1] == '#') last_col_has = true;
    }
    ensuref(first_col_has, "The first column must contain at least one '#'");
    ensuref(last_col_has, "The last column must contain at least one '#'");

    // No extra content
    inf.readEof();
    return 0;
}
