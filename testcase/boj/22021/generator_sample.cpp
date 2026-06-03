#include "testlib.h"

#include <array>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(30, 40);
    array<array<int, 8>, 8> sprayer{};

    int mode = rnd.next(5);
    double plusBias = rnd.next(0.20, 0.80);

    vector<pair<int, int>> cells;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    auto place = [&](int r, int c) {
        if (sprayer[r][c] != 0) {
            return;
        }
        sprayer[r][c] = (rnd.next() < plusBias ? 1 : -1);
    };

    if (mode == 0) {
        int count = rnd.next(0, 6);
        for (int i = 0; i < count; ++i) {
            place(cells[i].first, cells[i].second);
        }
    } else if (mode == 1) {
        int count = rnd.next(7, 18);
        for (int i = 0; i < count; ++i) {
            place(cells[i].first, cells[i].second);
        }
    } else if (mode == 2) {
        int row = rnd.next(8);
        int col = rnd.next(8);
        for (int c = 0; c < 8; ++c) {
            if (rnd.next() < 0.70) {
                place(row, c);
            }
        }
        for (int r = 0; r < 8; ++r) {
            if (rnd.next() < 0.70) {
                place(r, col);
            }
        }
    } else if (mode == 3) {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if ((r + c) % 2 == 0 && rnd.next() < 0.45) {
                    place(r, c);
                }
            }
        }
    } else {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (rnd.next() < 0.28) {
                    place(r, c);
                }
            }
        }
    }

    array<int, 8> rowSum{};
    array<int, 8> colSum{};
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            rowSum[r] += sprayer[r][c];
            colSum[c] += sprayer[r][c];
        }
    }

    println(m);
    for (int r = 0; r < 8; ++r) {
        vector<int> row;
        for (int c = 0; c < 8; ++c) {
            row.push_back(m + rowSum[r] + colSum[c] - sprayer[r][c]);
        }
        println(row);
    }

    return 0;
}
