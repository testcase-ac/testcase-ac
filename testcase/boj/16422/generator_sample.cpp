#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(6, 18);
    }

    int s;
    if (n == 1) {
        s = 1;
    } else {
        int sMode = rnd.next(0, 3);
        if (sMode == 0) s = 1;
        else if (sMode == 1) s = n;
        else if (sMode == 2) s = rnd.next(2, min(n, 5));
        else s = rnd.next(1, n);
    }

    vector<string> grid(n, string(n, 'C'));
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next(0, 1) ? 'D' : 'C';
            }
        }
    } else if (mode == 1) {
        char fill = rnd.next(0, 1) ? 'D' : 'C';
        for (int i = 0; i < n; ++i) grid[i] = string(n, fill);
    } else if (mode == 2) {
        int period = rnd.next(2, 4);
        bool horizontal = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int band = horizontal ? i : j;
                grid[i][j] = (band % period == 0) ? 'D' : 'C';
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0) ? 'D' : 'C';
            }
        }
    } else if (mode == 4) {
        int thickness = rnd.next(1, min(3, (n + 1) / 2));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i < thickness || j < thickness || i >= n - thickness || j >= n - thickness) {
                    grid[i][j] = 'D';
                }
            }
        }
    } else if (mode == 5) {
        int clusters = rnd.next(1, 4);
        for (int c = 0; c < clusters; ++c) {
            int r1 = rnd.next(0, n - 1);
            int c1 = rnd.next(0, n - 1);
            int r2 = rnd.next(r1, min(n - 1, r1 + rnd.next(0, 4)));
            int c2 = rnd.next(c1, min(n - 1, c1 + rnd.next(0, 4)));
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    grid[i][j] = 'D';
                }
            }
        }
    } else {
        int dirtyPercent = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next(1, 100) <= dirtyPercent ? 'D' : 'C';
            }
        }
    }

    println(n, s);
    for (const string& row : grid) println(row);

    return 0;
}
