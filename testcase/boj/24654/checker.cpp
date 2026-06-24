#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n;

struct Grid {
    vector<string> cells;
};

Grid readAnswer(InStream& stream) {
    Grid result;
    result.cells.resize(n);

    for (int i = 0; i < n; ++i) {
        result.cells[i] = stream.readToken(format("[BW]{%d}", n), format("row[%d]", i + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    vector<int> rowCounts(n, 0), colCounts(n, 0);
    int whiteCount = 0;
    pair<int, int> firstWhite = {-1, -1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (result.cells[i][j] == 'B') {
                ++rowCounts[i];
                ++colCounts[j];
            } else {
                ++whiteCount;
                if (firstWhite.first == -1) {
                    firstWhite = {i, j};
                }
            }
        }
    }

    vector<int> expected(n), sortedRows = rowCounts, sortedCols = colCounts;
    for (int i = 0; i < n; ++i) {
        expected[i] = i;
    }
    sort(sortedRows.begin(), sortedRows.end());
    sort(sortedCols.begin(), sortedCols.end());

    if (sortedRows != expected) {
        stream.quitf(_wa, "row black counts are not a permutation of 0..%d", n - 1);
    }
    if (sortedCols != expected) {
        stream.quitf(_wa, "column black counts are not a permutation of 0..%d", n - 1);
    }
    if (whiteCount == 0) {
        stream.quitf(_wa, "there are no white cells");
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    vector<vector<int>> seen(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    seen[firstWhite.first][firstWhite.second] = 1;
    q.push(firstWhite);
    int reachedWhite = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        ++reachedWhite;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }
            if (!seen[nr][nc] && result.cells[nr][nc] == 'W') {
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }

    if (reachedWhite != whiteCount) {
        stream.quitf(_wa, "white cells are not connected: reached %d of %d", reachedWhite, whiteCount);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (result.cells[i][j] != 'B') {
                continue;
            }

            bool hasWhiteNeighbor = false;
            for (int d = 0; d < 4; ++d) {
                int ni = i + dr[d];
                int nj = j + dc[d];
                if (0 <= ni && ni < n && 0 <= nj && nj < n && result.cells[ni][nj] == 'W') {
                    hasWhiteNeighbor = true;
                }
            }
            if (!hasWhiteNeighbor) {
                stream.quitf(_wa, "black cell (%d, %d) has no adjacent white cell", i + 1, j + 1);
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 500, "N");
    inf.readEoln();
    inf.readEof();

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid grid");
}
