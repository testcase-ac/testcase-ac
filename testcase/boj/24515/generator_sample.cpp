#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char letter(int x) {
    return char('A' + (x % 26));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 5);
    } else if (mode == 5) {
        n = rnd.next(10, 18);
    } else {
        n = rnd.next(4, 12);
    }

    vector<string> grid(n, string(n, 'A'));

    if (mode == 0) {
        char c = letter(rnd.next(26));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = c;
            }
        }
    } else if (mode == 1) {
        int alphabet = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = letter(rnd.next(alphabet));
            }
        }
    } else if (mode == 2) {
        bool horizontal = rnd.next(2);
        int stripeWidth = rnd.next(1, 3);
        int offset = rnd.next(26);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int band = (horizontal ? i : j) / stripeWidth;
                grid[i][j] = letter(offset + band);
            }
        }
    } else if (mode == 3) {
        int a = rnd.next(26);
        int b = rnd.next(26);
        while (b == a) b = rnd.next(26);
        int period = rnd.next(2, 3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = ((i + j) % period == 0 ? letter(a) : letter(b));
            }
        }
    } else if (mode == 4) {
        int block = rnd.next(2, 4);
        int alphabet = rnd.next(3, 8);
        for (int bi = 0; bi < n; bi += block) {
            for (int bj = 0; bj < n; bj += block) {
                char c = letter(rnd.next(alphabet));
                for (int i = bi; i < n && i < bi + block; ++i) {
                    for (int j = bj; j < n && j < bj + block; ++j) {
                        grid[i][j] = c;
                    }
                }
            }
        }
    } else {
        int alphabet = rnd.next(4, 9);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int ring = min(min(i, j), min(n - 1 - i, n - 1 - j));
                grid[i][j] = letter(ring + rnd.next(alphabet));
            }
        }

        int row = rnd.next(1, n - 2);
        char wall = letter(rnd.next(26));
        for (int j = 0; j < n; ++j) {
            grid[row][j] = wall;
        }
        grid[row][rnd.next(n)] = letter(wall - 'A' + 1 + rnd.next(25));
    }

    grid[0][0] = '.';
    grid[n - 1][n - 1] = '.';

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
