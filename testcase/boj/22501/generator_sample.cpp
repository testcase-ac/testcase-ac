#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> allStamps() {
    vector<pair<int, int>> stamps;
    for (int h = 1; h <= 4; ++h) {
        for (int w = 1; w <= 4; ++w) {
            stamps.push_back({h, w});
        }
    }
    return stamps;
}

vector<pair<int, int>> chooseStamps() {
    vector<pair<int, int>> stamps = allStamps();
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        vector<pair<int, int>> basic = {{1, 1}, {2, 2}, {4, 4}};
        shuffle(basic.begin(), basic.end());
        basic.resize(rnd.next(1, (int)basic.size()));
        return basic;
    }

    if (mode == 1) {
        vector<pair<int, int>> lines;
        for (auto stamp : stamps) {
            if (stamp.first == 1 || stamp.second == 1) {
                lines.push_back(stamp);
            }
        }
        shuffle(lines.begin(), lines.end());
        lines.resize(rnd.next(1, (int)lines.size()));
        return lines;
    }

    if (mode == 2) {
        return stamps;
    }

    if (mode == 3) {
        vector<pair<int, int>> large;
        for (auto stamp : stamps) {
            if (stamp.first * stamp.second >= 6) {
                large.push_back(stamp);
            }
        }
        shuffle(large.begin(), large.end());
        large.resize(rnd.next(1, (int)large.size()));
        return large;
    }

    shuffle(stamps.begin(), stamps.end());
    int count = rnd.next(1, 16);
    stamps.resize(count);
    sort(stamps.begin(), stamps.end());
    return stamps;
}

vector<string> makeBoard() {
    const string colors = "RGB";
    vector<string> board(4, string(4, 'R'));
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        char c = rnd.any(colors);
        for (auto& row : board) {
            fill(row.begin(), row.end(), c);
        }
    } else if (mode == 1) {
        for (int r = 0; r < 4; ++r) {
            char c = rnd.any(colors);
            fill(board[r].begin(), board[r].end(), c);
        }
    } else if (mode == 2) {
        for (int c = 0; c < 4; ++c) {
            char color = rnd.any(colors);
            for (int r = 0; r < 4; ++r) {
                board[r][c] = color;
            }
        }
    } else if (mode == 3) {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                board[r][c] = colors[(r + c + rnd.next(0, 2)) % 3];
            }
        }
    } else if (mode == 4) {
        char quad[2][2];
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < 2; ++c) {
                quad[r][c] = rnd.any(colors);
            }
        }
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                board[r][c] = quad[r / 2][c / 2];
            }
        }
    } else {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                board[r][c] = rnd.any(colors);
            }
        }
    }

    if (rnd.next(0, 3) == 0) {
        int changes = rnd.next(1, 4);
        for (int i = 0; i < changes; ++i) {
            board[rnd.next(0, 3)][rnd.next(0, 3)] = rnd.any(colors);
        }
    }

    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> stamps = chooseStamps();
    vector<string> board = makeBoard();

    println((int)stamps.size());
    for (auto stamp : stamps) {
        println(stamp.first, stamp.second);
    }
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
