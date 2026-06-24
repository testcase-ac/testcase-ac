#include "testlib.h"

#include <queue>
#include <string>
#include <vector>

using namespace std;

int n, c, e;

struct Answer {
    bool possible;
};

int connectedCount(const vector<string>& grid, char target) {
    vector<vector<int>> seen(n, vector<int>(n, 0));
    queue<pair<int, int>> q;

    for (int i = 0; i < n && q.empty(); ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == target) {
                seen[i][j] = 1;
                q.push({i, j});
                break;
            }
        }
    }

    int count = 0;
    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto [r, col] = q.front();
        q.pop();
        ++count;

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = col + dc[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }
            if (seen[nr][nc] || grid[nr][nc] != target) {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    return count;
}

Answer readAnswer(InStream& stream) {
    int claim = stream.readInt(-1, 1, "claim");
    if (claim == 0) {
        stream.quitf(_wa, "claim must be -1 or 1");
    }

    if (claim == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {false};
    }

    vector<string> grid(n);
    int count1 = 0;
    int count2 = 0;

    for (int i = 0; i < n; ++i) {
        grid[i] = stream.readToken(format("[012]{%d}", n), format("row[%d]", i + 1).c_str());
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                ++count1;
            } else if (grid[i][j] == '2') {
                ++count2;
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    if (count1 != c) {
        stream.quitf(_wa, "space 1 has size %d instead of %d", count1, c);
    }
    if (count2 != e) {
        stream.quitf(_wa, "space 2 has size %d instead of %d", count2, e);
    }

    if (connectedCount(grid, '1') != c) {
        stream.quitf(_wa, "space 1 is not connected");
    }
    if (connectedCount(grid, '2') != e) {
        stream.quitf(_wa, "space 2 is not connected");
    }

    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    for (int r = 0; r < n; ++r) {
        for (int col = 0; col < n; ++col) {
            if (grid[r][col] != '1') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = col + dc[dir];
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                    continue;
                }
                if (grid[nr][nc] == '2') {
                    stream.quitf(_wa, "spaces 1 and 2 are adjacent at (%d, %d) and (%d, %d)",
                                 r + 1, col + 1, nr + 1, nc + 1);
                }
            }
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    c = inf.readInt();
    e = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible && !participant.possible) {
        quitf(_wa, "participant reports impossible but jury provides a valid partition");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provides a valid partition while jury reports impossible");
    }

    quitf(_ok, "%s", participant.possible ? "valid partition" : "impossible matches jury");
}
