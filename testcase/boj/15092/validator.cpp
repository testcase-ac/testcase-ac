#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    const string rowPattern = "[#.]{%d,%d}";
    vector<string> grid(m);
    for (int i = 0; i < m; ++i) {
        grid[i] = inf.readLine(format(rowPattern.c_str(), n, n), "row");
    }

    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != '#') {
                continue;
            }

            int blackNeighbors = 0;
            for (int dir = 0; dir < 8; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (0 <= nr && nr < m && 0 <= nc && nc < n && grid[nr][nc] == '#') {
                    ++blackNeighbors;
                }
            }
            ensuref(blackNeighbors == 2,
                    "black pixel at row %d column %d has %d black neighbors, expected 2",
                    r + 1,
                    c + 1,
                    blackNeighbors);
        }
    }

    inf.readEof();
}
