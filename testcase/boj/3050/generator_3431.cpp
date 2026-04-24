#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid dimensions
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);
    vector<string> grid(R, string(C, 'X'));

    // Choose generation mode for diversity
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Uniform random emptiness
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (rnd.next() < p) grid[i][j] = '.';
            }
        }
    }
    else if (mode == 1) {
        // Single corridor (row or column) plus sparse random
        bool horiz = rnd.next(0, 1);
        if (horiz) {
            int r0 = rnd.next(0, R - 1);
            for (int j = 0; j < C; j++) grid[r0][j] = '.';
        } else {
            int c0 = rnd.next(0, C - 1);
            for (int i = 0; i < R; i++) grid[i][c0] = '.';
        }
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'X' && rnd.next() < p)
                    grid[i][j] = '.';
            }
        }
    }
    else {
        // One solid block of empties plus random elsewhere
        int r1 = rnd.next(0, R - 1);
        int r2 = rnd.next(r1, R - 1);
        int c1 = rnd.next(0, C - 1);
        int c2 = rnd.next(c1, C - 1);
        for (int i = r1; i <= r2; i++) {
            for (int j = c1; j <= c2; j++) {
                grid[i][j] = '.';
            }
        }
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'X' && rnd.next() < p)
                    grid[i][j] = '.';
            }
        }
    }

    // Ensure at least one empty cell
    bool anyEmpty = false;
    for (int i = 0; i < R && !anyEmpty; i++)
        for (int j = 0; j < C; j++)
            if (grid[i][j] == '.') { anyEmpty = true; break; }
    if (!anyEmpty) {
        int i = rnd.next(0, R - 1);
        int j = rnd.next(0, C - 1);
        grid[i][j] = '.';
    }

    // Output
    printf("%d %d\n", R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
