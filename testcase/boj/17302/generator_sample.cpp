#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 7) {
        n = rnd.next(10, 18);
        m = rnd.next(10, 18);
    }

    vector<string> grid(n, string(m, 'W'));

    if (mode == 0 || mode == 1) {
        int period = rnd.next(1, 4);
        int phase = rnd.next(period);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int pos = i + j;
                if ((pos + phase) % period == 0 || rnd.next(10) == 0) {
                    grid[i][j] = 'B';
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(2) ? 'B' : 'W';
            }
        }
    } else if (mode == 3) {
        char fill = rnd.next(2) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            grid[i].assign(m, fill);
        }
    } else if (mode == 4) {
        int rowPeriod = rnd.next(1, 4);
        int colPeriod = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i % rowPeriod == 0 || j % colPeriod == 0) {
                    grid[i][j] = 'B';
                }
            }
        }
    } else if (mode == 5) {
        int phase = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j + phase) % 2 == 0) ? 'B' : 'W';
            }
        }
    } else if (mode == 6) {
        bool blackBorder = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool border = i == 0 || i == n - 1 || j == 0 || j == m - 1;
                grid[i][j] = (border == blackBorder) ? 'B' : 'W';
            }
        }
    } else {
        int blackChance = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (rnd.next(10) < blackChance) ? 'B' : 'W';
            }
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
