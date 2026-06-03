#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int R = 1, C = 1;
    vector<string> grid;

    if (mode == 0) {
        R = rnd.next(1, 3);
        C = rnd.next(1, 8);
    } else if (mode == 1) {
        R = rnd.next(1, 8);
        C = rnd.next(1, 3);
    } else if (mode == 2) {
        R = rnd.next(2, 8);
        C = rnd.next(2, 8);
    } else if (mode == 3) {
        R = rnd.next(4, 12);
        C = rnd.next(4, 12);
    } else if (mode == 4) {
        R = rnd.next(1, 2);
        C = rnd.next(2, 10);
    } else {
        R = rnd.next(2, 10);
        C = rnd.next(1, 2);
    }

    grid.assign(R, string(C, '.'));

    if (mode <= 3) {
        int sheepWeight = rnd.next(1, 8);
        int wolfWeight = rnd.next(1, 8);
        int emptyWeight = rnd.next(4, 20);
        int total = sheepWeight + wolfWeight + emptyWeight;

        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                int pick = rnd.next(1, total);
                if (pick <= sheepWeight) {
                    grid[r][c] = 'S';
                } else if (pick <= sheepWeight + wolfWeight) {
                    grid[r][c] = 'W';
                }
            }
        }
    } else {
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                grid[r][c] = (r + c) % 2 == 0 ? 'S' : '.';
            }
        }
    }

    if (mode >= 4) {
        int r = rnd.next(0, R - 1);
        int c = rnd.next(0, C - 1);
        vector<pair<int, int>> neighbors;
        if (r > 0) neighbors.push_back({r - 1, c});
        if (r + 1 < R) neighbors.push_back({r + 1, c});
        if (c > 0) neighbors.push_back({r, c - 1});
        if (c + 1 < C) neighbors.push_back({r, c + 1});

        if (!neighbors.empty()) {
            pair<int, int> wolf = rnd.any(neighbors);
            grid[r][c] = 'S';
            grid[wolf.first][wolf.second] = 'W';
        }
    }

    println(R, C);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
