#include "testlib.h"

#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Answer {
    int blackComponents;
    int whiteComponents;
    int rows;
    int cols;
};

int expectedBlack;
int expectedWhite;

int countComponents(const vector<string>& grid, char color) {
    const int rows = (int)grid.size();
    const int cols = (int)grid[0].size();
    vector<vector<int>> visited(rows, vector<int>(cols, 0));
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    int components = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != color || visited[r][c]) {
                continue;
            }
            ++components;
            queue<pair<int, int>> q;
            q.push({r, c});
            visited[r][c] = 1;

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                for (int dir = 0; dir < 4; ++dir) {
                    int nr = cr + dr[dir];
                    int nc = cc + dc[dir];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                        continue;
                    }
                    if (visited[nr][nc] || grid[nr][nc] != color) {
                        continue;
                    }
                    visited[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    return components;
}

Answer readAnswer(InStream& stream) {
    int rows = stream.readInt(1, 100000, "r");
    int cols = stream.readInt(1, 100000, "c");
    long long tiles = 1LL * rows * cols;
    if (tiles > 100000) {
        stream.quitf(_wa, "panel has too many tiles: r=%d c=%d tiles=%lld", rows, cols, tiles);
    }

    vector<string> grid(rows);
    for (int r = 0; r < rows; ++r) {
        grid[r] = stream.readToken("[@.]+", format("row[%d]", r + 1).c_str());
        if ((int)grid[r].size() != cols) {
            stream.quitf(_wa,
                         "row %d has length %d instead of %d",
                         r + 1,
                         (int)grid[r].size(),
                         cols);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after panel");
    }

    Answer answer;
    answer.blackComponents = countComponents(grid, '@');
    answer.whiteComponents = countComponents(grid, '.');
    answer.rows = rows;
    answer.cols = cols;

    if (answer.blackComponents != expectedBlack || answer.whiteComponents != expectedWhite) {
        stream.quitf(_wa,
                     "component counts are black=%d white=%d, expected black=%d white=%d",
                     answer.blackComponents,
                     answer.whiteComponents,
                     expectedBlack,
                     expectedWhite);
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    expectedBlack = inf.readInt();
    expectedWhite = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid panel: black=%d white=%d, participant size=%dx%d, jury size=%dx%d",
          participant.blackComponents,
          participant.whiteComponents,
          participant.rows,
          participant.cols,
          jury.rows,
          jury.cols);
}
