#include "testlib.h"
using namespace std;

bool inside(int i, int j, int n) {
    return (0 <= i && i < n && 0 <= j && j < n);
}

bool canPlaceWhite(int i, int j, const vector<string>& b) {
    int n = (int)b.size();
    if (b[i][j] == 'o') return false;
    static const int di[4] = {-1, 1, 0, 0};
    static const int dj[4] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        int ni = i + di[d], nj = j + dj[d];
        if (inside(ni, nj, n) && b[ni][nj] == 'o') return false;
    }
    return true;
}

void ensureLiberties(vector<string>& b) {
    int n = (int)b.size();
    static const int di[4] = {-1, 1, 0, 0};
    static const int dj[4] = {0, 0, -1, 1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] != 'o') continue;
            bool hasEmpty = false;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inside(ni, nj, n)) continue;
                if (b[ni][nj] == '.') {
                    hasEmpty = true;
                    break;
                }
            }
            if (hasEmpty) continue;

            // Need to create at least one liberty by turning an adjacent 'x' into '.'
            vector<pair<int,int>> cand;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inside(ni, nj, n)) continue;
                if (b[ni][nj] != 'o') cand.push_back({ni, nj});
            }
            if (!cand.empty()) {
                auto p = rnd.any(cand);
                b[p.first][p.second] = '.';
            }
        }
    }
}

void addFarRandomDots(vector<string>& b, double prob) {
    int n = (int)b.size();
    vector<vector<bool>> near(n, vector<bool>(n, false));
    static const int di[5] = {0, -1, 1, 0, 0};
    static const int dj[5] = {0, 0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] == 'o') {
                for (int d = 0; d < 5; d++) {
                    int ni = i + di[d], nj = j + dj[d];
                    if (inside(ni, nj, n)) near[ni][nj] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!near[i][j] && b[i][j] == 'x') {
                if (rnd.next() < prob) b[i][j] = '.';
            }
        }
    }
}

vector<string> genRandomBoard(int N, double pWhite, double pBlack) {
    vector<string> b(N, string(N, '.'));
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cells.push_back({i, j});
    shuffle(cells.begin(), cells.end());

    for (auto &cell : cells) {
        int i = cell.first, j = cell.second;
        if (rnd.next() < pWhite && canPlaceWhite(i, j, b)) {
            b[i][j] = 'o';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (b[i][j] == '.' && rnd.next() < pBlack) {
                b[i][j] = 'x';
            }
        }
    }

    ensureLiberties(b);
    return b;
}

vector<string> genLinePattern() {
    int N = rnd.next(5, 12);
    vector<string> b(N, string(N, 'x'));

    int r = rnd.next(1, N - 2);
    int maxK = min((N - 1) / 2, 6);
    if (maxK < 2) maxK = 2;
    int K = rnd.next(2, maxK);

    for (int t = 0; t < K; t++) {
        int c = 1 + 2 * t;
        if (c >= N) break;
        b[r][c] = 'o';
        if (c - 1 >= 0) b[r][c - 1] = '.';
        if (c + 1 < N) b[r][c + 1] = '.';
    }

    addFarRandomDots(b, 0.3);
    ensureLiberties(b);
    return b;
}

vector<string> genClusterPattern() {
    int N = rnd.next(7, 15);
    vector<string> b(N, string(N, 'x'));
    int target = rnd.next(1, 3);
    int created = 0;
    int attempts = 0;
    static const int di[4] = {-1, 1, 0, 0};
    static const int dj[4] = {0, 0, -1, 1};

    while (created < target && attempts < 1000) {
        attempts++;
        int ci = rnd.next(1, N - 2);
        int cj = rnd.next(1, N - 2);
        if (b[ci][cj] != 'x') continue;

        vector<pair<int,int>> newWhites;
        b[ci][cj] = '.'; // center

        for (int d = 0; d < 4; d++) {
            int ni = ci + di[d], nj = cj + dj[d];
            if (!inside(ni, nj, N)) continue;
            if (!canPlaceWhite(ni, nj, b)) continue;
            if (rnd.next() < 0.8) {
                b[ni][nj] = 'o';
                newWhites.push_back({ni, nj});
            }
        }

        if ((int)newWhites.size() >= 2) {
            created++;
        } else {
            // revert
            b[ci][cj] = 'x';
            for (auto &p : newWhites) b[p.first][p.second] = 'x';
        }
    }

    if (created == 0) {
        // Fallback to a generic random board
        return genRandomBoard(N, 0.2, 0.5);
    }

    addFarRandomDots(b, 0.4);
    ensureLiberties(b);
    return b;
}

vector<string> genDenseBlacksPattern() {
    int N = rnd.next(7, 15);
    vector<string> b(N, string(N, 'x'));
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cells.push_back({i, j});
    shuffle(cells.begin(), cells.end());

    static const int di[4] = {-1, 1, 0, 0};
    static const int dj[4] = {0, 0, -1, 1};
    double pAttemptWhite = 0.3;

    for (auto &cell : cells) {
        int i = cell.first, j = cell.second;
        if (rnd.next() < pAttemptWhite && canPlaceWhite(i, j, b)) {
            b[i][j] = 'o';
            vector<pair<int,int>> neigh;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inside(ni, nj, N)) continue;
                if (b[ni][nj] != 'o') neigh.push_back({ni, nj});
            }
            if (!neigh.empty()) {
                auto p = rnd.any(neigh);
                if (b[p.first][p.second] == 'x')
                    b[p.first][p.second] = '.';
            }
        }
    }

    addFarRandomDots(b, 0.15);
    ensureLiberties(b);
    return b;
}

vector<string> genExtremePattern() {
    int N = rnd.next(3, 10);
    int st = rnd.next(0, 3);
    vector<string> b;

    if (st == 0) {
        // All empty
        b.assign(N, string(N, '.'));
    } else if (st == 1) {
        // All black
        b.assign(N, string(N, 'x'));
    } else if (st == 2) {
        // Single white with random surroundings
        b.assign(N, string(N, '.'));
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        b[i][j] = 'o';
        static const int di[4] = {-1, 1, 0, 0};
        static const int dj[4] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (!inside(ni, nj, N)) continue;
            if (rnd.next() < 0.5) b[ni][nj] = 'x';
        }
        ensureLiberties(b);
    } else { // st == 3
        // Checkerboard-like many whites
        b.assign(N, string(N, '.'));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((i + j) % 2 == 0 && rnd.next() < 0.8) {
                    if (canPlaceWhite(i, j, b)) b[i][j] = 'o';
                }
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (b[i][j] == '.' && rnd.next() < 0.3) {
                    b[i][j] = 'x';
                }
            }
        }
        ensureLiberties(b);
    }

    return b;
}

void assertValid(const vector<string>& b) {
    int n = (int)b.size();
    static const int di[4] = {-1, 1, 0, 0};
    static const int dj[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] != 'o') continue;

            bool hasEmpty = false;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inside(ni, nj, n)) continue;
                if (b[ni][nj] == 'o') {
                    ensuref(false,
                            "Adjacent whites at (%d,%d) and (%d,%d)",
                            i + 1, j + 1, ni + 1, nj + 1);
                }
                if (b[ni][nj] == '.') hasEmpty = true;
            }
            ensuref(hasEmpty,
                    "White at (%d,%d) has no empty neighbor",
                    i + 1, j + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board;
    int type = rnd.next(0, 5);

    if (type == 0) {
        int N = rnd.next(3, 6);
        board = genRandomBoard(N, 0.2, 0.3);
    } else if (type == 1) {
        int N = rnd.next(6, 12);
        board = genRandomBoard(N, 0.3, 0.6);
    } else if (type == 2) {
        board = genLinePattern();
    } else if (type == 3) {
        board = genClusterPattern();
    } else if (type == 4) {
        board = genDenseBlacksPattern();
    } else { // type == 5
        board = genExtremePattern();
    }

    assertValid(board);

    int N = (int)board.size();
    println(N);
    for (int i = 0; i < N; i++) {
        println(board[i]);
    }

    return 0;
}
