#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int r, c;
};

struct Component {
    int r1, r2, c1, c2;
    vector<Point> cells;
    int zr1, zr2, zc1, zc2;
};

int n, u, v, w, x, y;
vector<vector<int>> board;
vector<Component> components;
vector<vector<int>> compId;

bool inside(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

void readInput() {
    n = inf.readInt();
    u = inf.readInt();
    v = inf.readInt();
    w = inf.readInt();
    x = inf.readInt();
    y = inf.readInt();

    board.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = inf.readInt();
        }
    }
}

void buildComponents() {
    compId.assign(n, vector<int>(n, -1));
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    for (int sr = 0; sr < n; ++sr) {
        for (int sc = 0; sc < n; ++sc) {
            if (board[sr][sc] == 0 || compId[sr][sc] != -1) {
                continue;
            }

            int id = (int)components.size();
            Component comp;
            comp.r1 = comp.c1 = n;
            comp.r2 = comp.c2 = -1;
            queue<Point> q;
            q.push({sr, sc});
            compId[sr][sc] = id;

            while (!q.empty()) {
                Point cur = q.front();
                q.pop();
                comp.cells.push_back(cur);
                comp.r1 = min(comp.r1, cur.r);
                comp.r2 = max(comp.r2, cur.r);
                comp.c1 = min(comp.c1, cur.c);
                comp.c2 = max(comp.c2, cur.c);

                for (int d = 0; d < 4; ++d) {
                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];
                    if (inside(nr, nc) && board[nr][nc] == 1 && compId[nr][nc] == -1) {
                        compId[nr][nc] = id;
                        q.push({nr, nc});
                    }
                }
            }

            comp.zr1 = comp.zc1 = n;
            comp.zr2 = comp.zc2 = -1;
            for (int r = comp.r1; r <= comp.r2; ++r) {
                for (int c = comp.c1; c <= comp.c2; ++c) {
                    if (board[r][c] == 0) {
                        comp.zr1 = min(comp.zr1, r - comp.r1);
                        comp.zr2 = max(comp.zr2, r - comp.r1);
                        comp.zc1 = min(comp.zc1, c - comp.c1);
                        comp.zc2 = max(comp.zc2, c - comp.c1);
                    }
                }
            }

            components.push_back(comp);
        }
    }
}

bool areaClear(int r1, int r2, int c1, int c2) {
    if (r1 < 0 || c1 < 0 || r2 >= n || c2 >= n) {
        return false;
    }
    for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c) {
            if (board[r][c] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool isValidClaim(int row, int col) {
    int r = row - 1;
    int c = col - 1;
    if (!inside(r, c) || board[r][c] == 0) {
        return false;
    }

    const Component& comp = components[compId[r][c]];
    if (comp.r1 != r || comp.c1 != c || comp.zr2 < comp.zr1 || comp.zc2 < comp.zc1) {
        return false;
    }

    int height = comp.r2 - comp.r1 + 1;
    int width = comp.c2 - comp.c1 + 1;
    int holeHeight = comp.zr2 - comp.zr1 + 1;
    int holeWidth = comp.zc2 - comp.zc1 + 1;
    bool top = comp.zr1 == 0;
    bool bottom = comp.zr2 == height - 1;
    bool left = comp.zc1 == 0;
    bool right = comp.zc2 == width - 1;
    if ((int)top + (int)bottom + (int)left + (int)right != 1) {
        return false;
    }

    if (top) {
        if (holeHeight != x || holeWidth != y) {
            return false;
        }
        return width == u && comp.zc1 == u - y - w && areaClear(comp.r1 - v, comp.r1 - 1, comp.c1, comp.c2);
    }
    if (bottom) {
        if (holeHeight != x || holeWidth != y) {
            return false;
        }
        return width == u && comp.zc1 == w && areaClear(comp.r2 + 1, comp.r2 + v, comp.c1, comp.c2);
    }
    if (left) {
        if (holeHeight != y || holeWidth != x) {
            return false;
        }
        return height == u && comp.zr1 == w && areaClear(comp.r1, comp.r2, comp.c1 - v, comp.c1 - 1);
    }
    if (holeHeight != y || holeWidth != x) {
        return false;
    }
    return height == u && comp.zr1 == u - y - w && areaClear(comp.r1, comp.r2, comp.c2 + 1, comp.c2 + v);
}

struct Answer {
    vector<pair<int, int>> coords;
};

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(0, n * n, "count");
    vector<pair<int, int>> coords;
    set<pair<int, int>> seen;

    for (int i = 0; i < count; ++i) {
        int row = stream.readInt(1, n, format("row[%d]", i + 1).c_str());
        int col = stream.readInt(1, n, format("col[%d]", i + 1).c_str());
        pair<int, int> coord = {row, col};
        if (!seen.insert(coord).second) {
            stream.quitf(_wa, "duplicate coordinate (%d, %d)", row, col);
        }
        if (!isValidClaim(row, col)) {
            stream.quitf(_wa, "coordinate (%d, %d) is not a valid fitting block", row, col);
        }
        coords.push_back(coord);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after coordinate list");
    }
    sort(coords.begin(), coords.end());
    return {coords};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    readInput();
    buildComponents();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    set<pair<int, int>> jurySet(jury.coords.begin(), jury.coords.end());
    for (auto [row, col] : participant.coords) {
        if (!jurySet.count({row, col})) {
            quitf(_fail, "participant reported valid coordinate (%d, %d) omitted by jury", row, col);
        }
    }

    if (participant.coords.size() != jury.coords.size()) {
        quitf(_wa, "missing fitting block: expected %d entries, found %d entries",
              (int)jury.coords.size(), (int)participant.coords.size());
    }

    quitf(_ok, "accepted %d fitting blocks", (int)participant.coords.size());
}
