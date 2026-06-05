#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Point {
    int y;
    int x;
};

void placeObjects(vector<string>& grid) {
    int h = (int)grid.size();
    int w = (int)grid[0].size();
    Point terra{rnd.next(0, h - 1), rnd.next(0, w - 1)};
    Point exit{rnd.next(0, h - 1), rnd.next(0, w - 1)};
    while (exit.y == terra.y && exit.x == terra.x) {
        exit = {rnd.next(0, h - 1), rnd.next(0, w - 1)};
    }
    grid[terra.y][terra.x] = 'T';
    grid[exit.y][exit.x] = 'E';
}

void printCase(const vector<string>& grid) {
    println((int)grid[0].size(), (int)grid.size());
    for (const string& row : grid) {
        println(row);
    }
}

vector<string> randomDigits(int h, int w, int maxDigit) {
    vector<string> grid(h, string(w, '0'));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            grid[y][x] = char('0' + rnd.next(0, maxDigit));
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int h = rnd.next(2, 12);
    int w = rnd.next(2, 12);
    int maxDigit = rnd.next(1, 9);
    vector<string> grid = randomDigits(h, w, maxDigit);

    if (mode == 0) {
        placeObjects(grid);
    } else if (mode == 1) {
        if (h < 4) h = 4;
        if (w < 4) w = 4;
        grid = randomDigits(h, w, maxDigit);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (y == 0 || y == h - 1 || x == 0 || x == w - 1) {
                    grid[y][x] = 'R';
                }
            }
        }
        int row = rnd.next(1, h - 2);
        grid[row][1] = 'T';
        grid[row][w - 2] = 'E';
        for (int x = 2; x < w - 2; ++x) {
            grid[row][x] = char('0' + rnd.next(0, maxDigit));
        }
    } else if (mode == 2) {
        double holeProb = rnd.next(0.15, 0.40);
        double rockProb = rnd.next(0.05, 0.25);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                double roll = rnd.next();
                if (roll < holeProb) {
                    grid[y][x] = 'H';
                } else if (roll < holeProb + rockProb) {
                    grid[y][x] = 'R';
                }
            }
        }
        placeObjects(grid);
    } else if (mode == 3) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if ((y + x) % 3 == 0 && rnd.next(0, 1) == 0) {
                    grid[y][x] = 'R';
                } else if ((y * 2 + x) % 5 == 0 && rnd.next(0, 2) == 0) {
                    grid[y][x] = 'H';
                }
            }
        }
        placeObjects(grid);
    } else {
        h = rnd.next(2, 4);
        w = rnd.next(2, 4);
        grid = randomDigits(h, w, maxDigit);
        placeObjects(grid);
    }

    printCase(grid);
    return 0;
}
