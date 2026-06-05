#include "testlib.h"

#include <array>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(30, 40);
    int mode = rnd.next(0, 5);
    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = rnd.next(2, 6);
    } else if (mode == 2) {
        k = rnd.next(7, 16);
    } else if (mode == 3) {
        k = rnd.next(17, 32);
    } else {
        k = rnd.next(48, 63);
    }

    vector<pair<int, int>> cells;
    if (mode == 1) {
        int row = rnd.next(0, 7);
        for (int col = 0; col < 8; ++col) {
            cells.push_back({row, col});
        }
        for (int r = 0; r < 8; ++r) {
            if (r != row) {
                cells.push_back({r, rnd.next(0, 7)});
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < 8; ++i) {
            cells.push_back({i, i});
            cells.push_back({i, 7 - i});
        }
    } else {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                cells.push_back({r, c});
            }
        }
    }
    shuffle(cells.begin(), cells.end());

    array<array<int, 8>, 8> board{};
    for (int r = 0; r < 8; ++r) {
        board[r].fill(m);
    }

    for (int idx = 0; idx < k; ++idx) {
        int r = cells[idx].first;
        int c = cells[idx].second;
        int delta;
        if (mode == 0) {
            delta = rnd.next(0, 1) == 0 ? -1 : 1;
        } else if (mode == 3) {
            delta = (r + c + rnd.next(0, 1)) % 2 == 0 ? 1 : -1;
        } else {
            delta = rnd.next(0, 99) < 60 ? 1 : -1;
        }

        for (int i = 0; i < 8; ++i) {
            board[i][c] += delta;
        }
        for (int j = 0; j < 8; ++j) {
            board[r][j] += delta;
        }
        board[r][c] -= delta;
    }

    println(m);
    println(k);
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (c > 0) {
                printf(" ");
            }
            printf("%d", board[r][c]);
        }
        printf("\n");
    }

    return 0;
}
