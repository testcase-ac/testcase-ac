#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid dimensions
    int h = rnd.next(1, 12);
    int w = rnd.next(1, 12);
    vector<string> grid(h, string(w, '_'));
    // Choose a pattern scenario for variability
    int type = rnd.next(0, 4);
    if (type == 0) {
        // Random density
        int p = rnd.any(vector<int>{10, 30, 50, 70, 90});
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (rnd.next(0, 99) < p)
                    grid[i][j] = 'C';
        // Ensure at least one C
        bool anyC = false;
        for (auto &row : grid)
            for (char c : row)
                if (c == 'C') anyC = true;
        if (!anyC) {
            int i = rnd.next(0, h-1), j = rnd.next(0, w-1);
            grid[i][j] = 'C';
        }
    } else if (type == 1) {
        // Anti-diagonal: maximal antichain
        int m = min(h, w);
        for (int i = 0; i < m; i++)
            grid[i][w - 1 - i] = 'C';
    } else if (type == 2) {
        // Single row with random Cs
        int r = rnd.next(0, h-1);
        int ccount = rnd.next(1, w);
        vector<int> cols(w);
        iota(cols.begin(), cols.end(), 0);
        shuffle(cols.begin(), cols.end());
        for (int k = 0; k < ccount; k++)
            grid[r][cols[k]] = 'C';
    } else if (type == 3) {
        // Filled block
        int r1 = rnd.next(0, h-1);
        int r2 = rnd.next(r1, h-1);
        int c1 = rnd.next(0, w-1);
        int c2 = rnd.next(c1, w-1);
        for (int i = r1; i <= r2; i++)
            for (int j = c1; j <= c2; j++)
                grid[i][j] = 'C';
    } else {
        // Zigzag chain (one C per row, monotonic)
        int curr = 0;
        for (int i = 0; i < h; i++) {
            int c = rnd.next(curr, w-1);
            grid[i][c] = 'C';
            curr = c;
        }
    }
    // Output
    println(h, w);
    for (int i = 0; i < h; i++)
        printf("%s\n", grid[i].c_str());
    return 0;
}
