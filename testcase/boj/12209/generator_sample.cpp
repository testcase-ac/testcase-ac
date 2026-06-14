#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int randomTile(int maxPower) {
    if (rnd.next(100) < 35) {
        return 0;
    }
    return 1 << rnd.next(1, maxPower);
}

int mergeFriendlyTile(int basePower, int offset) {
    int power = basePower + offset;
    while (power > 10) {
        power -= 3;
    }
    return 1 << power;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> dirs = {"left", "right", "up", "down"};

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 8);
        if (mode == 4) {
            n = rnd.next(9, 20);
        }

        string dir = dirs[rnd.next(static_cast<int>(dirs.size()))];
        println(n, dir);

        vector<vector<int>> board(n, vector<int>(n, 0));
        int maxPower = rnd.next(1, 10);

        if (mode == 0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    board[i][j] = randomTile(maxPower);
                }
            }
        } else if (mode == 1) {
            int basePower = rnd.next(1, 8);
            for (int i = 0; i < n; ++i) {
                int current = mergeFriendlyTile(basePower, i % 3);
                for (int j = 0; j < n; ++j) {
                    if (rnd.next(100) < 20) {
                        board[i][j] = 0;
                    } else if (j > 0 && rnd.next(100) < 65) {
                        board[i][j] = board[i][j - 1];
                    } else {
                        board[i][j] = current;
                    }
                }
            }
        } else if (mode == 2) {
            int basePower = rnd.next(1, 8);
            for (int j = 0; j < n; ++j) {
                int current = mergeFriendlyTile(basePower, j % 3);
                for (int i = 0; i < n; ++i) {
                    if (rnd.next(100) < 20) {
                        board[i][j] = 0;
                    } else if (i > 0 && rnd.next(100) < 65) {
                        board[i][j] = board[i - 1][j];
                    } else {
                        board[i][j] = current;
                    }
                }
            }
        } else if (mode == 3) {
            int first = 1 << rnd.next(1, 9);
            int second = 1 << rnd.next(1, 9);
            if (first == second) {
                second = first == 1024 ? 512 : first * 2;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (rnd.next(100) < 15) {
                        board[i][j] = 0;
                    } else {
                        board[i][j] = ((i + j) % 2 == 0) ? first : second;
                    }
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int power = 1 + ((i * 3 + j * 5 + rnd.next(4)) % 10);
                    board[i][j] = rnd.next(100) < 12 ? 0 : (1 << power);
                }
            }
        }

        for (const auto& row : board) {
            println(row);
        }
    }

    return 0;
}
