#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct State {
    int rr, rc, br, bc;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 10, "N");
    inf.readSpace();
    int M = inf.readInt(3, 10, "M");
    inf.readEoln();

    vector<string> board(N);
    int holeR = -1, holeC = -1;
    int redR = -1, redC = -1;
    int blueR = -1, blueC = -1;

    for (int i = 0; i < N; ++i) {
        board[i] = inf.readToken("[.#ORB]{1,10}", "row");
        inf.readEoln();
        ensuref((int)board[i].size() == M,
                "Row %d length is %d, expected %d", i, (int)board[i].size(), M);
        for (int j = 0; j < M; ++j) {
            char ch = board[i][j];
            if (ch == 'O') {
                ensuref(holeR == -1,
                        "Multiple holes: already at (%d,%d), another at (%d,%d)",
                        holeR, holeC, i, j);
                holeR = i; holeC = j;
            } else if (ch == 'R') {
                ensuref(redR == -1,
                        "Multiple red balls: already at (%d,%d), another at (%d,%d)",
                        redR, redC, i, j);
                redR = i; redC = j;
            } else if (ch == 'B') {
                ensuref(blueR == -1,
                        "Multiple blue balls: already at (%d,%d), another at (%d,%d)",
                        blueR, blueC, i, j);
                blueR = i; blueC = j;
            }
        }
    }

    // Global constraints from statement
    ensuref(holeR != -1, "There must be exactly one hole 'O'");
    ensuref(redR  != -1, "There must be exactly one red ball 'R'");
    ensuref(blueR != -1, "There must be exactly one blue ball 'B'");

    // Borders are all walls '#'
    for (int j = 0; j < M; ++j) {
        ensuref(board[0][j] == '#', "Top border at (0,%d) must be '#'", j);
        ensuref(board[N-1][j] == '#', "Bottom border at (%d,%d) must be '#'", N-1, j);
    }
    for (int i = 0; i < N; ++i) {
        ensuref(board[i][0] == '#', "Left border at (%d,0) must be '#'", i);
        ensuref(board[i][M-1] == '#', "Right border at (%d,%d) must be '#'", i, M-1);
    }

    // R, B, O not on walls (interior only)
    auto ensureInterior = [&](int r, int c, char what) {
        ensuref(r > 0 && r < N-1 && c > 0 && c < M-1,
                "%c must be inside the border, but is at (%d,%d)", what, r, c);
        ensuref(board[r][c] != '#',
                "%c must not be on a wall, but board[%d][%d] is '#'", what, r, c);
    };
    ensureInterior(holeR, holeC, 'O');
    ensureInterior(redR,  redC,  'R');
    ensureInterior(blueR, blueC, 'B');

    // R, B, O distinct cells
    ensuref(!(redR == blueR && redC == blueC), "Red and Blue balls share a cell");
    ensuref(!(redR == holeR && redC == holeC), "Red ball on the hole initially");
    ensuref(!(blueR == holeR && blueC == holeC), "Blue ball on the hole initially");

    // Simulate to ensure "answer is at most 10 or -1": existence of solution within 10 moves
    // BFS on state space (rr, rc, br, bc)
    const int dr[4] = {0, 0, -1, 1}; // L, R, U, D
    const int dc[4] = {-1, 1, 0, 0};

    auto roll = [&](int r, int c, int dir, bool& inHole, int otherR, int otherC) {
        inHole = false;
        while (true) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (board[nr][nc] == '#') break;
            if (nr == otherR && nc == otherC) break; // other ball blocks
            if (nr == holeR && nc == holeC) {
                inHole = true;
                r = nr; c = nc;
                break;
            }
            r = nr; c = nc;
        }
        return make_pair(r, c);
    };

    bool visited[10][10][10][10] = {};
    queue<pair<State,int>> q;
    State start{redR, redC, blueR, blueC};
    visited[redR][redC][blueR][blueC] = true;
    q.push({start, 0});
    bool solvableWithin10 = false;

    while (!q.empty()) {
        auto cur = q.front().first;
        int d = q.front().second;
        q.pop();
        if (d >= 10) continue; // we only care up to 10 moves

        for (int dir = 0; dir < 4; ++dir) {
            // Decide movement order based on direction
            bool firstIsRed;
            if (dir == 0)      firstIsRed = (cur.rc < cur.bc); // L: smaller column first
            else if (dir == 1) firstIsRed = (cur.rc > cur.bc); // R: larger column first
            else if (dir == 2) firstIsRed = (cur.rr < cur.br); // U: smaller row first
            else               firstIsRed = (cur.rr > cur.br); // D: larger row first

            bool redHole = false, blueHole = false;
            int r1r, r1c, r2r, r2c, b1r, b1c, b2r, b2c;

            if (firstIsRed) {
                auto p1 = roll(cur.rr, cur.rc, dir, redHole,
                               cur.br, cur.bc);
                r1r = p1.first; r1c = p1.second;
                auto p2 = roll(cur.br, cur.bc, dir, blueHole,
                               redHole ? -1 : r1r, redHole ? -1 : r1c);
                b1r = p2.first; b1c = p2.second;
            } else {
                auto p1 = roll(cur.br, cur.bc, dir, blueHole,
                               cur.rr, cur.rc);
                b1r = p1.first; b1c = p1.second;
                auto p2 = roll(cur.rr, cur.rc, dir, redHole,
                               blueHole ? -1 : b1r, blueHole ? -1 : b1c);
                r1r = p2.first; r1c = p2.second;
            }

            if (blueHole) continue;          // fail state
            if (redHole) {                   // success within <=10
                solvableWithin10 = true;
                // No need to continue BFS further
                while (!q.empty()) q.pop();
                break;
            }

            State nxt{r1r, r1c, b1r, b1c};
            if (!visited[nxt.rr][nxt.rc][nxt.br][nxt.bc]) {
                visited[nxt.rr][nxt.rc][nxt.br][nxt.bc] = true;
                q.push({nxt, d + 1});
            }
        }
    }

    // According to statement: if cannot solve within 10 moves, answer is -1.
    // That is consistent with our model for all boards, so no explicit ensuref needed.

    inf.readEof();
}
