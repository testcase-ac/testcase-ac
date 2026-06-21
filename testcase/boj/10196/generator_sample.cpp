#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int h = rnd.next(1, 10);
        int w = rnd.next(1, 10);

        if (mode == 0) {
            h = rnd.next(1, 3);
            w = rnd.next(1, 3);
        } else if (mode == 1) {
            if (rnd.next(0, 1) == 0) {
                h = 1;
                w = rnd.next(1, 12);
            } else {
                h = rnd.next(1, 12);
                w = 1;
            }
        }

        vector<string> grid(h, string(w, 'O'));

        if (mode == 0 || mode == 1) {
            double blockProb = rnd.next(0.0, 0.55);
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (rnd.next() < blockProb) grid[i][j] = 'X';
                }
            }
        } else if (mode == 2) {
            double blockProb = rnd.next(0.05, 0.45);
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (rnd.next() < blockProb) grid[i][j] = 'X';
                }
            }

            int turnRow = rnd.next(0, h - 1);
            for (int j = 0; j < w; ++j) grid[turnRow][j] = 'O';
            for (int i = 0; i <= turnRow; ++i) grid[i][0] = 'O';
            for (int i = turnRow; i < h; ++i) grid[i][w - 1] = 'O';
        } else if (mode == 3) {
            double blockProb = rnd.next(0.0, 0.25);
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (rnd.next() < blockProb) grid[i][j] = 'X';
                }
            }

            if (h > 1 && w > 1) {
                if (rnd.next(0, 1) == 0) {
                    int row = rnd.next(0, h - 2);
                    for (int j = 0; j < w; ++j) grid[row][j] = 'X';
                } else {
                    int col = rnd.next(0, w - 2);
                    for (int i = 0; i < h; ++i) grid[i][col] = 'X';
                }
            } else {
                grid[0][0] = 'X';
            }
        } else if (mode == 4) {
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    bool blocked = ((i + j + rnd.next(0, 1)) % 2 == 0);
                    if (blocked && rnd.next() < 0.75) grid[i][j] = 'X';
                }
            }
            grid[0][0] = rnd.next(0, 4) == 0 ? 'X' : 'O';
            grid[h - 1][w - 1] = rnd.next(0, 4) == 0 ? 'X' : 'O';
        } else {
            double blockProb = rnd.next(0.15, 0.65);
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (rnd.next() < blockProb) grid[i][j] = 'X';
                }
            }
            if (rnd.next(0, 2) != 0) grid[0][0] = 'O';
            if (rnd.next(0, 2) != 0) grid[h - 1][w - 1] = 'O';
        }

        println(h, w);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
