#include "testlib.h"
using namespace std;

bool placeH(vector<string>& g, int i, int j) {
    int r = (int)g.size();
    int c = (int)g[0].size();
    if (j + 2 >= c) return false;
    const char pat[3] = {'>', 'o', '<'};
    for (int k = 0; k < 3; ++k) {
        if (g[i][j + k] != '.' && g[i][j + k] != pat[k]) return false;
    }
    for (int k = 0; k < 3; ++k) g[i][j + k] = pat[k];
    return true;
}

bool placeV(vector<string>& g, int i, int j) {
    int r = (int)g.size();
    int c = (int)g[0].size();
    if (i + 2 >= r) return false;
    const char pat[3] = {'v', 'o', '^'};
    for (int k = 0; k < 3; ++k) {
        if (g[i + k][j] != '.' && g[i + k][j] != pat[k]) return false;
    }
    for (int k = 0; k < 3; ++k) g[i + k][j] = pat[k];
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);

    const string shells = "o<>v^";

    for (int tc = 0; tc < T; ++tc) {
        // blank line before each test case
        printf("\n");

        int mode = rnd.next(0, 4);
        int r = 1, c = 1;

        if (mode == 4) {
            // Single row or single column with at most one clear candy
            if (rnd.next(0, 1) == 0) {
                r = 1;
                c = rnd.next(1, 10);
            } else {
                c = 1;
                r = rnd.next(1, 10);
            }
        } else if (mode == 0) {
            // Pure noisy random grid
            r = rnd.next(1, 8);
            c = rnd.next(1, 8);
        } else if (mode == 1) {
            // Several non-overlapping candies
            r = rnd.next(3, 8);
            c = rnd.next(3, 8);
        } else if (mode == 2) {
            // Overlapping cross-shaped candies in the interior
            r = rnd.next(3, 7);
            c = rnd.next(3, 7);
        } else { // mode == 3
            // Candies touching the borders
            r = rnd.next(2, 9);
            c = rnd.next(2, 9);
        }

        vector<string> grid(r, string(c, '.'));

        if (mode == 4) {
            // Single row/column case
            if (r == 1 && c >= 3 && rnd.next(0, 1) == 1) {
                int j = rnd.next(0, c - 3);
                grid[0][j] = '>';
                grid[0][j + 1] = 'o';
                grid[0][j + 2] = '<';
            } else if (c == 1 && r >= 3 && rnd.next(0, 1) == 1) {
                int i = rnd.next(0, r - 3);
                grid[i][0] = 'v';
                grid[i + 1][0] = 'o';
                grid[i + 2][0] = '^';
            }
            // light noise
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    if (grid[i][j] == '.' && rnd.next(0, 9) >= 7)
                        grid[i][j] = rnd.any(shells);
        } else if (mode == 0) {
            // Pure noise, no deliberate candies
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    int x = rnd.next(0, 9);
                    if (x < 5) grid[i][j] = '.';
                    else grid[i][j] = rnd.any(shells);
                }
            }
        } else if (mode == 1) {
            // Several non-overlapping candies, small number
            int maxH = (c >= 3 ? 2 : 0);
            int maxV = (r >= 3 ? 2 : 0);
            int wantH = (maxH > 0 ? rnd.next(0, maxH) : 0);
            int wantV = (maxV > 0 ? rnd.next(0, maxV) : 0);

            // place horizontals
            int placedH = 0;
            for (int i = 0; i < r && placedH < wantH; ++i) {
                for (int j = 0; j + 2 < c && placedH < wantH; ++j) {
                    if (rnd.next(0, 1) && placeH(grid, i, j))
                        ++placedH;
                }
            }
            // place verticals
            int placedV = 0;
            for (int j = 0; j < c && placedV < wantV; ++j) {
                for (int i = 0; i + 2 < r && placedV < wantV; ++i) {
                    if (rnd.next(0, 1) && placeV(grid, i, j))
                        ++placedV;
                }
            }
            // noise in remaining cells
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    if (grid[i][j] == '.' && rnd.next(0, 9) >= 6)
                        grid[i][j] = rnd.any(shells);
        } else if (mode == 2) {
            // Overlapping cross in the middle
            int ci = rnd.next(1, max(1, r - 2));
            int cj = rnd.next(1, max(1, c - 2));
            if (r >= 3 && c >= 3) {
                placeH(grid, ci, cj - 1);
                placeV(grid, ci - 1, cj);
            }
            // light noise
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    if (grid[i][j] == '.' && rnd.next(0, 9) >= 7)
                        grid[i][j] = rnd.any(shells);
        } else { // mode == 3
            // Border-touching candies
            if (c >= 3) {
                placeH(grid, 0, 0);                 // top-left
                if (r > 1) placeH(grid, r - 1, max(0, c - 3)); // bottom-right-ish
            }
            if (r >= 3) {
                placeV(grid, 0, 0);                 // top-left column
                if (c > 1) placeV(grid, max(0, r - 3), c - 1); // bottom-right column
            }
            // mixed noise
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    if (grid[i][j] == '.' && rnd.next(0, 9) >= 5)
                        grid[i][j] = rnd.any(shells);
        }

        println(r, c);
        for (int i = 0; i < r; ++i)
            println(grid[i]);
    }

    return 0;
}
