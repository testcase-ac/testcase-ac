#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = rnd.next(1, 6);
    int c = rnd.next(1, 6);
    int h = rnd.next(1, 5);

    if (mode == 0) {
        r = rnd.next(1, 2);
        c = rnd.next(1, 8);
        h = rnd.next(1, 2);
    } else if (mode == 1) {
        r = rnd.next(3, 7);
        c = rnd.next(3, 7);
        h = rnd.next(2, 4);
    } else if (mode == 2) {
        r = rnd.next(1, 3);
        c = rnd.next(3, 8);
        h = rnd.next(3, 6);
    } else if (mode == 3) {
        r = rnd.next(3, 6);
        c = rnd.next(3, 6);
        h = 1;
    } else if (mode == 4) {
        r = rnd.next(2, 5);
        c = 1;
        h = rnd.next(2, 6);
    }

    vector<vector<string>> cube(h, vector<string>(r, string(c, '.')));

    if (mode == 0) {
        int mines = rnd.next(0, r * c * h);
        for (int i = 0; i < mines; ++i) {
            cube[rnd.next(0, h - 1)][rnd.next(0, r - 1)][rnd.next(0, c - 1)] = '*';
        }
    } else if (mode == 1) {
        for (int z = 0; z < h; ++z) {
            for (int y = 0; y < r; ++y) {
                for (int x = 0; x < c; ++x) {
                    if (rnd.next(0, 99) < 70) cube[z][y][x] = '*';
                }
            }
        }
    } else if (mode == 2) {
        for (int z = 0; z < h; ++z) {
            for (int y = 0; y < r; ++y) {
                for (int x = 0; x < c; ++x) {
                    bool stripe = (x + z) % rnd.next(2, 3) == 0;
                    if (stripe || rnd.next(0, 99) < 15) cube[z][y][x] = '*';
                }
            }
        }
    } else if (mode == 3) {
        for (int y = 0; y < r; ++y) {
            for (int x = 0; x < c; ++x) {
                if (y == 0 || x == 0 || y == r - 1 || x == c - 1) {
                    if (rnd.next(0, 99) < 65) cube[0][y][x] = '*';
                } else if (rnd.next(0, 99) < 20) {
                    cube[0][y][x] = '*';
                }
            }
        }
    } else if (mode == 4) {
        for (int z = 0; z < h; ++z) {
            for (int y = 0; y < r; ++y) {
                if ((y + z) % 2 == 0 || rnd.next(0, 99) < 25) cube[z][y][0] = '*';
            }
        }
    } else {
        int threshold = rnd.next(10, 55);
        for (int z = 0; z < h; ++z) {
            for (int y = 0; y < r; ++y) {
                for (int x = 0; x < c; ++x) {
                    if (rnd.next(0, 99) < threshold) cube[z][y][x] = '*';
                }
            }
        }
    }

    println(r, c, h);
    for (int z = 0; z < h; ++z) {
        for (int y = 0; y < r; ++y) {
            println(cube[z][y]);
        }
    }

    return 0;
}
