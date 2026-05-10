#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: width (columns), M: height (rows)
    int N = inf.readInt(3, 50, "N");
    inf.readSpace();
    int M = inf.readInt(3, 50, "M");
    inf.readEoln();

    vector<string> grid(M);
    int sx = -1, sy = -1;
    int ex = -1, ey = -1;
    int itemCount = 0;

    for (int i = 0; i < M; ++i) {
        grid[i] = inf.readLine("[^]+", "row");
        ensuref((int)grid[i].size() == N,
                "Row %d must have exactly %d characters, but has %d",
                i + 1, N, (int)grid[i].size());

        for (int j = 0; j < N; ++j) {
            char c = grid[i][j];
            ensuref(c == '.' || c == '#' || c == 'S' || c == 'E' || c == 'X',
                    "Invalid character '%c' at row %d, col %d", c, i + 1, j + 1);

            if (c == 'S') {
                ensuref(sx == -1,
                        "Multiple starting positions 'S' found (latest at row %d, col %d)",
                        i + 1, j + 1);
                sx = j;
                sy = i;
            } else if (c == 'E') {
                ensuref(ex == -1,
                        "Multiple exits 'E' found (latest at row %d, col %d)",
                        i + 1, j + 1);
                ex = j;
                ey = i;
            } else if (c == 'X') {
                ++itemCount;
                ensuref(itemCount <= 5,
                        "Number of items 'X' exceeds 5 (at row %d, col %d)",
                        i + 1, j + 1);
            }
        }
    }

    // Check that S and E exist exactly once
    ensuref(sx != -1 && sy != -1, "Starting position 'S' must appear exactly once");
    ensuref(ex != -1 && ey != -1, "Exit 'E' must appear exactly once");

    // House is surrounded by walls (#). The statement's example shows that the
    // border includes the outer boundary, and E is on that boundary but not a wall.
    // Thus we check:
    // - All border cells must be '#', except the single exit cell, which must be 'E'.
    int borderECount = 0;

    // Top and bottom rows
    for (int j = 0; j < N; ++j) {
        // Top row
        if (sy == 0 && sx == j) {
            // S cannot be on the border; it must be surrounded by walls only
            ensuref(false,
                    "Top border cell at row 1, col %d cannot be 'S'; borders must be walls except exit 'E'",
                    j + 1);
        }
        if (ey == 0 && ex == j) {
            ensuref(grid[0][j] == 'E',
                    "Top border exit at row 1, col %d must be 'E'", j + 1);
            borderECount++;
        } else {
            ensuref(grid[0][j] == '#',
                    "Top border cell at row 1, col %d must be '#'", j + 1);
        }

        // Bottom row
        if (sy == M - 1 && sx == j) {
            ensuref(false,
                    "Bottom border cell at row %d, col %d cannot be 'S'; borders must be walls except exit 'E'",
                    M, j + 1);
        }
        if (ey == M - 1 && ex == j) {
            ensuref(grid[M - 1][j] == 'E',
                    "Bottom border exit at row %d, col %d must be 'E'", M, j + 1);
            borderECount++;
        } else {
            ensuref(grid[M - 1][j] == '#',
                    "Bottom border cell at row %d, col %d must be '#'", M, j + 1);
        }
    }

    // Left and right columns (excluding corners already checked)
    for (int i = 1; i < M - 1; ++i) {
        // Left column
        if (sy == i && sx == 0) {
            ensuref(false,
                    "Left border cell at row %d, col 1 cannot be 'S'; borders must be walls except exit 'E'",
                    i + 1);
        }
        if (ey == i && ex == 0) {
            ensuref(grid[i][0] == 'E',
                    "Left border exit at row %d, col 1 must be 'E'", i + 1);
            borderECount++;
        } else {
            ensuref(grid[i][0] == '#',
                    "Left border cell at row %d, col 1 must be '#'", i + 1);
        }

        // Right column
        if (sy == i && sx == N - 1) {
            ensuref(false,
                    "Right border cell at row %d, col %d cannot be 'S'; borders must be walls except exit 'E'",
                    i + 1, N);
        }
        if (ey == i && ex == N - 1) {
            ensuref(grid[i][N - 1] == 'E',
                    "Right border exit at row %d, col %d must be 'E'", i + 1, N);
            borderECount++;
        } else {
            ensuref(grid[i][N - 1] == '#',
                    "Right border cell at row %d, col %d must be '#'", i + 1, N);
        }
    }

    // The unique exit must be on the border according to "집은 언제나 벽으로 둘러싸여 있고, 나가는 문은 언제나 하나이다."
    ensuref(borderECount == 1,
            "Exit 'E' must be exactly one cell on the border; found %d border exits", borderECount);

    // Validate the guarantee:
    // "모든 물건을 챙길 수 없는 경우는 주어지지 않는다."
    // -> from S it must be possible to collect all X's and then reach E.
    // We verify via BFS over (y, x, mask_of_collected_items).

    // Map each 'X' to an index 0..itemCount-1
    vector<vector<int>> itemId(M, vector<int>(N, -1));
    int curId = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'X') {
                itemId[i][j] = curId++;
            }
        }
    }
    ensuref(curId == itemCount, "Internal error: mismatched item count");

    int maxMask = (itemCount == 0 ? 1 : (1 << itemCount));
    vector<vector<vector<bool>>> vis(
        M, vector<vector<bool>>(N, vector<bool>(maxMask, false)));

    queue<tuple<int,int,int>> q;
    int startMask = 0;
    if (grid[sy][sx] == 'X') {
        int id = itemId[sy][sx];
        if (id >= 0) startMask |= (1 << id);
    }
    vis[sy][sx][startMask] = true;
    q.emplace(sy, sx, startMask);

    int fullMask = (itemCount == 0 ? 0 : (1 << itemCount) - 1);
    bool reachable = false;

    const int dy[4] = {-1, 1, 0, 0};
    const int dx[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [y, x, mask] = q.front();
        q.pop();

        if (y == ey && x == ex && mask == fullMask) {
            reachable = true;
            break;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (ny < 0 || ny >= M || nx < 0 || nx >= N) continue;
            char c = grid[ny][nx];
            if (c == '#') continue;

            int nmask = mask;
            if (c == 'X') {
                int id = itemId[ny][nx];
                if (id >= 0) nmask |= (1 << id);
            }
            if (!vis[ny][nx][nmask]) {
                vis[ny][nx][nmask] = true;
                q.emplace(ny, nx, nmask);
            }
        }
    }

    ensuref(reachable,
            "From 'S' it must be possible to collect all items and reach 'E', "
            "but no such path exists in this input");

    inf.readEof();
}
