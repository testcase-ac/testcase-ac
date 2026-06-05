#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

const int DY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inside(int n, int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < n;
}

void printBoard(const vector<string>& board) {
    println((int)board.size());
    for (const string& row : board) {
        println(row);
    }
}

void addRay(vector<string>& board, int y, int x, int dir, int len) {
    int n = board.size();
    for (int step = 1; step <= len; ++step) {
        int ny = y + DY[dir] * step;
        int nx = x + DX[dir] * step;
        if (inside(n, ny, nx)) {
            board[ny][nx] = 'W';
        }
    }

    int by = y + DY[dir] * (len + 1);
    int bx = x + DX[dir] * (len + 1);
    if (inside(n, by, bx)) {
        board[by][bx] = 'B';
    }
}

int maxRayLength(int n, int y, int x, int dir) {
    int length = 0;
    while (inside(n, y + DY[dir] * (length + 2), x + DX[dir] * (length + 2))) {
        ++length;
    }
    return length;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 20);
    if (mode == 5) {
        n = rnd.next(40, 80);
    }

    vector<string> board(n, string(n, '.'));

    if (mode == 0) {
        char stone = rnd.next(0, 1) ? 'W' : 'B';
        double fill = rnd.next(0.20, 0.80);
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (rnd.next() < fill) {
                    board[y][x] = stone;
                }
            }
        }
    } else if (mode == 1) {
        double emptyProb = rnd.next(0.05, 0.30);
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (rnd.next() < emptyProb) {
                    board[y][x] = '.';
                } else {
                    board[y][x] = rnd.next(0, 1) ? 'B' : 'W';
                }
            }
        }
    } else if (mode == 2) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                board[y][x] = rnd.next(0, 3) == 0 ? '.' : rnd.any(string("BW"));
            }
        }
    } else {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                board[y][x] = rnd.next(0, 9) == 0 ? '.' : rnd.any(string("BW"));
            }
        }

        int centers = mode == 3 ? rnd.next(1, 3) : rnd.next(3, 8);
        for (int i = 0; i < centers; ++i) {
            int y = rnd.next(0, n - 1);
            int x = rnd.next(0, n - 1);
            board[y][x] = '.';

            vector<int> dirs;
            for (int dir = 0; dir < 8; ++dir) {
                if (maxRayLength(n, y, x, dir) > 0) {
                    dirs.push_back(dir);
                }
            }
            shuffle(dirs.begin(), dirs.end());

            int useDirs = min((int)dirs.size(), rnd.next(1, 5));
            for (int j = 0; j < useDirs; ++j) {
                int limit = maxRayLength(n, y, x, dirs[j]);
                addRay(board, y, x, dirs[j], rnd.next(1, limit));
            }
        }
    }

    if (rnd.next(0, 4) == 0) {
        board[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '.';
    }

    bool hasEmpty = false;
    for (const string& row : board) {
        for (char cell : row) {
            hasEmpty = hasEmpty || cell == '.';
        }
    }
    if (!hasEmpty) {
        board[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '.';
    }

    printBoard(board);
    return 0;
}
