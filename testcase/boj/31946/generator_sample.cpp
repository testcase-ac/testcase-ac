#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    int x = rnd.next(1, 10);
    vector<vector<int>> grid(n, vector<int>(m, rnd.next(0, 1)));

    if (mode == 0) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            fill(grid[i].begin(), grid[i].end(), color);
        x = rnd.next(1, min(10, max(n, m)));
    } else if (mode == 1) {
        int offset = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = (i + j + offset) % 2;
        x = rnd.next(1, 3);
    } else if (mode == 2) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = (rnd.next(0, 99) < 75 ? color : 1 - color);
        grid[0][0] = color;
        grid[n - 1][m - 1] = 1 - color;
    } else if (mode == 3) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = rnd.next(0, 99) < 55 ? color : 1 - color;
        for (int i = 0; i < n; ++i)
            grid[i][0] = color;
        for (int j = 0; j < m; ++j)
            grid[n - 1][j] = color;
        x = rnd.next(1, 2);
    } else if (mode == 4) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = (i % 2 == 0 ? color : 1 - color);
        x = rnd.next(1, 4);
    } else if (mode == 5) {
        int color = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = (j % 2 == 0 ? color : 1 - color);
        x = rnd.next(1, 4);
    } else {
        int threshold = rnd.next(15, 85);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = rnd.next(0, 99) < threshold ? 0 : 1;
    }

    println(n);
    println(m);
    for (int i = 0; i < n; ++i)
        println(grid[i]);
    println(x);

    return 0;
}
