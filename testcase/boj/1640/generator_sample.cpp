#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

static int oddInRange(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x % 2 == 0) {
        if (x == hi) --x;
        else ++x;
    }
    return x;
}

static vector<string> blankGrid(int n, int m) {
    return vector<string>(n, string(m, '0'));
}

static void flipCell(vector<string>& grid, int r, int c) {
    grid[r][c] = grid[r][c] == '0' ? '1' : '0';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;

    if (mode == 0) {
        n = 1;
        m = oddInRange(1, 19);
    } else if (mode == 1) {
        n = oddInRange(1, 19);
        m = 1;
    } else if (mode == 7) {
        n = oddInRange(21, 39);
        m = oddInRange(21, 39);
    } else {
        n = oddInRange(1, 15);
        m = oddInRange(1, 15);
    }

    vector<string> grid = blankGrid(n, m);

    if (mode == 2) {
        char fill = rnd.next(0, 1) ? '1' : '0';
        for (string& row : grid) row.assign(m, fill);
    } else if (mode == 3) {
        int offset = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = ((i + j + offset) % 2) ? '1' : '0';
    } else if (mode == 4) {
        bool rowStripes = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int index = rowStripes ? i : j;
                int period = rnd.next(2, 4);
                grid[i][j] = (index % period == 0) ? '1' : '0';
            }
        }
    } else if (mode == 5) {
        int rowFlips = rnd.next(0, n);
        int colFlips = rnd.next(0, m);
        vector<int> rows(n), cols(m);
        for (int i = 0; i < n; ++i) rows[i] = i;
        for (int j = 0; j < m; ++j) cols[j] = j;
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());

        for (int k = 0; k < rowFlips; ++k)
            for (int j = 0; j < m; ++j)
                flipCell(grid, rows[k], j);
        for (int k = 0; k < colFlips; ++k)
            for (int i = 0; i < n; ++i)
                flipCell(grid, i, cols[k]);
    } else {
        double density;
        int densityMode = rnd.next(0, 3);
        if (densityMode == 0) density = rnd.next(0.05, 0.25);
        else if (densityMode == 1) density = rnd.next(0.35, 0.65);
        else if (densityMode == 2) density = rnd.next(0.75, 0.95);
        else density = rnd.next(0.0, 1.0);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (rnd.next() < density)
                    grid[i][j] = '1';
    }

    println(n, m);
    for (const string& row : grid) println(row);

    return 0;
}
