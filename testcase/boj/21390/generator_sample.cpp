#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

bool canPlace(const vector<string>& board, int r, int c, char ch) {
    if (c == 0 || c + 1 == (int)board[r].size()) {
        return false;
    }

    int h = board.size();
    int w = board[r].size();
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            int nr = r + dr;
            int nc = c + dc;
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                continue;
            }
            if (board[nr][nc] == ch) {
                return false;
            }
        }
    }
    return true;
}

void placeRandomCells(vector<string>& board, const vector<char>& alphabet, int attempts) {
    int h = board.size();
    int w = board[0].size();
    for (int it = 0; it < attempts; ++it) {
        int r = rnd.next(0, h - 1);
        int c = rnd.next(1, w - 2);
        char ch = rnd.any(alphabet);
        if (board[r][c] == '.' && canPlace(board, r, c, ch)) {
            board[r][c] = ch;
        }
    }
}

void placeAlternatingObstacles(vector<string>& board) {
    int h = board.size();
    int w = board[0].size();
    int parity = rnd.next(0, 1);
    for (int r = 0; r < h; ++r) {
        for (int c = 1; c + 1 < w; ++c) {
            if (((r + c) & 1) != parity) {
                continue;
            }
            if (rnd.next(100) < 65 && canPlace(board, r, c, '*')) {
                board[r][c] = '*';
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int h;
        int w;
        if (mode == 0) {
            h = rnd.next(1, 4);
            w = rnd.next(1, 8);
        } else {
            h = rnd.next(3, mode == 1 ? 8 : 12);
            w = rnd.next(3, mode == 1 ? 8 : 12);
        }

        vector<string> board(h, string(w, '.'));
        if (w >= 3) {
            if (mode == 1) {
                placeAlternatingObstacles(board);
                placeRandomCells(board, {'1', '5', '9'}, h * w / 3 + 1);
            } else if (mode == 2) {
                placeRandomCells(board, {'1', '2', '3', '7', '8', '9'}, h * w);
            } else if (mode == 3) {
                placeRandomCells(board, {'*'}, h * w / 2 + 1);
                placeRandomCells(board, {'1', '4', '6', '9'}, h * w / 2 + 1);
            } else if (mode == 4) {
                int c = rnd.next(1, w - 2);
                for (int r = 0; r < h; ++r) {
                    char ch = rnd.next(100) < 70 ? '*' : char('1' + rnd.next(9));
                    if (canPlace(board, r, c, ch)) {
                        board[r][c] = ch;
                    }
                    if (w > 4 && rnd.next(100) < 45) {
                        int other = rnd.next(1, w - 2);
                        char gate = char('1' + rnd.next(9));
                        if (board[r][other] == '.' && canPlace(board, r, other, gate)) {
                            board[r][other] = gate;
                        }
                    }
                }
            }
        }

        println(h, w);
        for (const string& row : board) {
            println(row);
        }
    }
}
