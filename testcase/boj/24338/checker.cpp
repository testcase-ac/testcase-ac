#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int R, C;
vector<string> originalGrid;
int startR, startC;

struct Answer {
    bool impossible;
    vector<string> grid;
};

bool isGoal(char cell) {
    return cell == 'P' || cell == 'B';
}

bool isHeightCell(char cell) {
    return cell == '.' || cell == 'P' || cell == 'B' || cell == '1';
}

int heightOf(char cell) {
    return cell == '1' ? 1 : 0;
}

bool isRamp(char cell) {
    return cell == 'N' || cell == 'W' || cell == 'E' || cell == 'S';
}

bool sideMatchesRamp(char ramp, int dr, int dc, int neighborHeight) {
    if (ramp == 'N') {
        return dc == 0 && ((dr == -1 && neighborHeight == 1) || (dr == 1 && neighborHeight == 0));
    }
    if (ramp == 'S') {
        return dc == 0 && ((dr == 1 && neighborHeight == 1) || (dr == -1 && neighborHeight == 0));
    }
    if (ramp == 'W') {
        return dr == 0 && ((dc == -1 && neighborHeight == 1) || (dc == 1 && neighborHeight == 0));
    }
    if (ramp == 'E') {
        return dr == 0 && ((dc == 1 && neighborHeight == 1) || (dc == -1 && neighborHeight == 0));
    }
    return false;
}

bool canMoveBetween(const vector<string>& grid, int r1, int c1, int r2, int c2) {
    char a = grid[r1][c1];
    char b = grid[r2][c2];
    if (a == '#' || b == '#') {
        return false;
    }

    int dr = r2 - r1;
    int dc = c2 - c1;

    if (isHeightCell(a) && isHeightCell(b)) {
        return heightOf(a) == heightOf(b);
    }
    if (isRamp(a) && isHeightCell(b)) {
        return sideMatchesRamp(a, dr, dc, heightOf(b));
    }
    if (isHeightCell(a) && isRamp(b)) {
        return sideMatchesRamp(b, -dr, -dc, heightOf(a));
    }
    return false;
}

bool canReachGoal(const vector<string>& grid) {
    vector<vector<int>> seen(R, vector<int>(C, 0));
    queue<pair<int, int>> q;
    seen[startR][startC] = 1;
    q.push({startR, startC});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (isGoal(originalGrid[r][c])) {
            return true;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || seen[nr][nc]) {
                continue;
            }
            if (!canMoveBetween(grid, r, c, nr, nc)) {
                continue;
            }
            seen[nr][nc] = 1;
            q.push({nr, nc});
        }
    }
    return false;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("(-1)|([.#1PBNWES]+)", "first output token");
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<string> grid(R);
    grid[0] = first;
    if ((int)grid[0].size() != C) {
        stream.quitf(_wa, "row 1 has length %d instead of %d", (int)grid[0].size(), C);
    }
    for (int r = 1; r < R; ++r) {
        grid[r] = stream.readToken("[.#1PBNWES]+", format("row[%d]", r + 1).c_str());
        if ((int)grid[r].size() != C) {
            stream.quitf(_wa, "row %d has length %d instead of %d", r + 1, (int)grid[r].size(), C);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            char expected = originalGrid[r][c];
            char found = grid[r][c];
            if (expected == '?') {
                if (!isRamp(found)) {
                    stream.quitf(_wa, "cell (%d,%d) must contain a ramp direction", r + 1, c + 1);
                }
            } else if (found != expected) {
                stream.quitf(_wa, "cell (%d,%d) changed from '%c' to '%c'", r + 1, c + 1, expected, found);
            }
        }
    }

    if (!canReachGoal(grid)) {
        stream.quitf(_wa, "completed grid does not let Gahee reach a pillow or bag");
    }

    return {false, grid};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    R = inf.readInt();
    C = inf.readInt();
    originalGrid.resize(R);
    for (int r = 0; r < R; ++r) {
        originalGrid[r] = inf.readToken();
    }
    startR = inf.readInt() - 1;
    startC = inf.readInt() - 1;

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid grid while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible but jury has a valid grid");
    }

    quitf(_ok, "valid completed grid");
}
