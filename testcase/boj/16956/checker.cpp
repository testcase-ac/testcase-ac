#include "testlib.h"

#include <queue>
#include <string>
#include <vector>
using namespace std;

int R, C;
vector<string> initialGrid;

bool hasAdjacentWolfSheep(const vector<string>& grid) {
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] != 'W') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (0 <= nr && nr < R && 0 <= nc && nc < C && grid[nr][nc] == 'S') {
                    return true;
                }
            }
        }
    }
    return false;
}

bool wolfCanReachSheep(const vector<string>& grid) {
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    vector<vector<int>> seen(R, vector<int>(C, 0));
    queue<pair<int, int>> q;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] == 'W') {
                seen[r][c] = 1;
                q.push({r, c});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (grid[r][c] == 'S') {
            return true;
        }
        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || seen[nr][nc] || grid[nr][nc] == 'D') {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }
    return false;
}

struct Answer {
    int possible;
    vector<string> grid;
};

Answer readAnswer(InStream& stream) {
    int possible = stream.readInt(0, 1, "possible");
    stream.readEoln();

    if (possible == 0) {
        stream.readEof();
        if (!hasAdjacentWolfSheep(initialGrid)) {
            stream.quitf(_wa, "reported impossible, but a valid fence placement exists");
        }
        return {0, {}};
    }

    vector<string> grid(R);
    string pattern = format("[.SWD]{%d}", C);
    for (int r = 0; r < R; ++r) {
        grid[r] = stream.readToken(pattern.c_str(), format("row[%d]", r + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (initialGrid[r][c] == 'S' && grid[r][c] != 'S') {
                stream.quitf(_wa, "sheep at row %d column %d was changed", r + 1, c + 1);
            }
            if (initialGrid[r][c] == 'W' && grid[r][c] != 'W') {
                stream.quitf(_wa, "wolf at row %d column %d was changed", r + 1, c + 1);
            }
            if (initialGrid[r][c] == '.' && grid[r][c] != '.' && grid[r][c] != 'D') {
                stream.quitf(_wa, "empty cell at row %d column %d was changed to %c",
                             r + 1, c + 1, grid[r][c]);
            }
        }
    }

    if (wolfCanReachSheep(grid)) {
        stream.quitf(_wa, "a wolf can reach a sheep");
    }

    return {1, grid};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    R = inf.readInt();
    C = inf.readInt();
    initialGrid.resize(R);
    for (int r = 0; r < R; ++r) {
        initialGrid[r] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible != participant.possible) {
        quitf(_fail, "jury and participant feasibility differ after validation");
    }
    quitf(_ok, "valid output");
}
