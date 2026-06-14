#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 8) {
        n = 30;
    } else {
        n = rnd.next(1, 14);
    }

    int a, b;
    int costMode = rnd.next(7);
    if (costMode == 0) {
        a = 0;
        b = rnd.next(0, 20);
    } else if (costMode == 1) {
        a = rnd.next(0, 20);
        b = 0;
    } else if (costMode == 2) {
        a = b = rnd.next(0, 1000000);
    } else if (costMode == 3) {
        a = rnd.next(0, 20);
        b = rnd.next(100000, 1000000);
    } else if (costMode == 4) {
        a = rnd.next(100000, 1000000);
        b = rnd.next(0, 20);
    } else {
        a = rnd.next(0, 1000000);
        b = rnd.next(0, 1000000);
    }

    vector<string> grid(n, string(n, '('));
    int mode = rnd.next(8);

    if (mode == 0) {
        char c = rnd.next(2) ? '(' : ')';
        for (int i = 0; i < n; ++i) {
            fill(grid[i].begin(), grid[i].end(), c);
        }
    } else if (mode == 1) {
        int flip = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = ((i + j + flip) % 2 == 0) ? '(' : ')';
            }
        }
    } else if (mode == 2) {
        bool horizontal = rnd.next(2);
        int stripe = rnd.next(1, max(1, min(n, 4)));
        int flip = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int band = horizontal ? i / stripe : j / stripe;
                grid[i][j] = ((band + flip) % 2 == 0) ? '(' : ')';
            }
        }
    } else if (mode == 3) {
        int splitRow = rnd.next(0, n);
        int splitCol = rnd.next(0, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool upperLeft = i < splitRow && j < splitCol;
                bool lowerRight = i >= splitRow && j >= splitCol;
                grid[i][j] = (upperLeft || lowerRight) ? '(' : ')';
            }
        }
    } else if (mode == 4) {
        int width = rnd.next(1, max(1, min(n, 5)));
        int flip = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = (((i + j) / width + flip) % 2 == 0) ? '(' : ')';
            }
        }
    } else if (mode == 5) {
        double p = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = (rnd.next() < p) ? '(' : ')';
            }
        }
    } else if (mode == 6) {
        char outside = rnd.next(2) ? '(' : ')';
        char inside = outside == '(' ? ')' : '(';
        for (int i = 0; i < n; ++i) {
            fill(grid[i].begin(), grid[i].end(), outside);
        }
        if (n > 2) {
            int r1 = rnd.next(0, n - 2);
            int c1 = rnd.next(0, n - 2);
            int r2 = rnd.next(r1 + 1, n - 1);
            int c2 = rnd.next(c1 + 1, n - 1);
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    grid[i][j] = inside;
                }
            }
        }
    } else {
        int walkCol = rnd.next(n);
        char path = rnd.next(2) ? '(' : ')';
        char other = path == '(' ? ')' : '(';
        for (int i = 0; i < n; ++i) {
            fill(grid[i].begin(), grid[i].end(), other);
            grid[i][walkCol] = path;
            if (rnd.next(100) < 35) {
                walkCol = max(0, min(n - 1, walkCol + rnd.next(-1, 1)));
            }
        }
    }

    println(n, a, b);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
