#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    vector<string> grid(n, string(m, 'O'));

    int si = rnd.next(0, n - 1);
    int sj = rnd.next(0, m - 1);

    if (mode == 0) {
        // Open campus with many reachable people.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 99) < 35) grid[i][j] = 'P';
            }
        }
    } else if (mode == 1) {
        // Densely walled campus, often separating people from the start.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < 45) grid[i][j] = 'X';
                else if (roll < 65) grid[i][j] = 'P';
            }
        }
    } else if (mode == 2) {
        // Checkerboard-like barriers catch solutions with mistaken movement rules.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j + rnd.next(0, 1)) % 3 == 0) grid[i][j] = 'X';
                else if (rnd.next(0, 99) < 30) grid[i][j] = 'P';
            }
        }
    } else if (mode == 3) {
        // Single-row or single-column corridors exercise boundary handling.
        if (rnd.next(0, 1) == 0) n = 1;
        else m = 1;
        grid.assign(n, string(m, 'O'));
        si = rnd.next(0, n - 1);
        sj = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < 25) grid[i][j] = 'X';
                else if (roll < 55) grid[i][j] = 'P';
            }
        }
    } else {
        // Tiny cases include the minimal 1x1 campus and small no-person layouts.
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        grid.assign(n, string(m, 'O'));
        si = rnd.next(0, n - 1);
        sj = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 99) < 25) grid[i][j] = 'P';
            }
        }
    }

    grid[si][sj] = 'I';

    println(n, m);
    for (const string& row : grid) println(row);

    return 0;
}
