#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int r;
    int c;
    vector<string> grid;
    int x;
    int y;
};

bool inside(int r, int c, int rows, int cols) {
    return 0 <= r && r < rows && 0 <= c && c < cols;
}

bool canPlaceQuestion(const vector<string>& grid, int r, int c) {
    if (grid[r][c] != '.') {
        return false;
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (inside(nr, nc, (int)grid.size(), (int)grid[0].size()) && grid[nr][nc] == '?') {
            return false;
        }
    }
    return true;
}

vector<pair<int, int>> shuffledCells(int r, int c) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());
    return cells;
}

void placeRandomGoals(CaseData& tc, int goalCount) {
    vector<pair<int, int>> cells = shuffledCells(tc.r, tc.c);
    int placed = 0;
    for (auto [r, c] : cells) {
        if (placed == goalCount) {
            return;
        }
        if (r == tc.x && c == tc.y) {
            continue;
        }
        if (tc.grid[r][c] == '.' || tc.grid[r][c] == '1') {
            tc.grid[r][c] = rnd.next(2) == 0 ? 'P' : 'B';
            ++placed;
        }
    }
}

CaseData randomGridCase() {
    int mode = rnd.next(4);
    int r = mode == 0 ? rnd.next(1, 4) : (mode == 1 ? rnd.next(5, 12) : rnd.next(2, 8));
    int c = mode == 0 ? rnd.next(1, 8) : (mode == 2 ? rnd.next(10, 22) : rnd.next(3, 12));
    CaseData tc{r, c, vector<string>(r, string(c, '.')), 0, 0};

    double wallProb = rnd.next(0.0, 0.28);
    double blockProb = rnd.next(0.0, 0.42);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            double roll = rnd.next();
            if (roll < wallProb) {
                tc.grid[i][j] = '#';
            } else if (roll < wallProb + blockProb) {
                tc.grid[i][j] = '1';
            }
        }
    }

    int wantQuestions = rnd.next(0, min(18, max(0, r * c / 3)));
    vector<pair<int, int>> cells = shuffledCells(r, c);
    int questions = 0;
    for (auto [i, j] : cells) {
        if (questions == wantQuestions) {
            break;
        }
        if (!canPlaceQuestion(tc.grid, i, j)) {
            continue;
        }
        tc.grid[i][j] = '?';
        ++questions;
    }

    cells = shuffledCells(r, c);
    for (auto [i, j] : cells) {
        if (tc.grid[i][j] != '#' && tc.grid[i][j] != '?') {
            tc.x = i;
            tc.y = j;
            break;
        }
    }
    tc.grid[tc.x][tc.y] = rnd.next(2) == 0 ? '.' : '1';

    placeRandomGoals(tc, rnd.next(1, min(3, r * c)));
    return tc;
}

CaseData corridorCase() {
    bool vertical = rnd.next(2) == 0;
    int len = rnd.next(5, 24);
    CaseData tc{vertical ? len : 1, vertical ? 1 : len, {}, 0, 0};
    tc.grid.assign(tc.r, string(tc.c, '.'));

    for (int i = 0; i < len; ++i) {
        int r = vertical ? i : 0;
        int c = vertical ? 0 : i;
        if (i % 4 == 2) {
            tc.grid[r][c] = '?';
        } else if (i % 4 == 0) {
            tc.grid[r][c] = '1';
        }
    }

    if (rnd.next(2)) {
        reverse(tc.grid.begin(), tc.grid.end());
        if (!vertical) {
            reverse(tc.grid[0].begin(), tc.grid[0].end());
        }
    }

    tc.x = 0;
    tc.y = 0;
    if (tc.grid[tc.x][tc.y] == '?') {
        tc.grid[tc.x][tc.y] = '.';
    }

    if (vertical) {
        tc.grid[tc.r - 1][0] = rnd.next(2) == 0 ? 'P' : 'B';
    } else {
        tc.grid[0][tc.c - 1] = rnd.next(2) == 0 ? 'P' : 'B';
    }
    return tc;
}

CaseData checkerboardRampCase() {
    int r = rnd.next(5, 10);
    int c = rnd.next(5, 10);
    CaseData tc{r, c, vector<string>(r, string(c, '.')), 0, 0};

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((i + j) % 3 == 0) {
                tc.grid[i][j] = '1';
            } else if (rnd.next(100) < 12) {
                tc.grid[i][j] = '#';
            }
        }
    }

    int questions = 0;
    for (int i = 1; i + 1 < r && questions < 18; i += 2) {
        for (int j = 1 + (i % 2); j + 1 < c && questions < 18; j += 3) {
            if (canPlaceQuestion(tc.grid, i, j)) {
                tc.grid[i][j] = '?';
                ++questions;
            }
        }
    }

    tc.x = rnd.next(r);
    tc.y = rnd.next(c);
    if (tc.grid[tc.x][tc.y] == '#' || tc.grid[tc.x][tc.y] == '?') {
        tc.grid[tc.x][tc.y] = '.';
    }
    placeRandomGoals(tc, rnd.next(1, 3));
    return tc;
}

CaseData wideBoundaryCase() {
    int r = rnd.next(1, 3);
    int c = rnd.next(25, 80);
    if (rnd.next(2)) {
        swap(r, c);
    }
    CaseData tc{r, c, vector<string>(r, string(c, '.')), 0, 0};

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (rnd.next(100) < 22) {
                tc.grid[i][j] = '1';
            } else if (rnd.next(100) < 8) {
                tc.grid[i][j] = '#';
            }
        }
    }

    int questions = 0;
    vector<pair<int, int>> cells = shuffledCells(r, c);
    for (auto [i, j] : cells) {
        if (questions == 18) {
            break;
        }
        if (canPlaceQuestion(tc.grid, i, j) && rnd.next(100) < 45) {
            tc.grid[i][j] = '?';
            ++questions;
        }
    }

    tc.x = rnd.next(r);
    tc.y = rnd.next(c);
    if (tc.grid[tc.x][tc.y] == '#' || tc.grid[tc.x][tc.y] == '?') {
        tc.grid[tc.x][tc.y] = '.';
    }
    placeRandomGoals(tc, rnd.next(1, 4));
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    CaseData tc;
    int mode = rnd.next(4);
    if (mode == 0) {
        tc = corridorCase();
    } else if (mode == 1) {
        tc = checkerboardRampCase();
    } else if (mode == 2) {
        tc = wideBoundaryCase();
    } else {
        tc = randomGridCase();
    }

    println(tc.r, tc.c);
    for (const string& row : tc.grid) {
        println(row);
    }
    println(tc.x + 1, tc.y + 1);
    return 0;
}
