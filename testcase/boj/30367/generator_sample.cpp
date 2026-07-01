#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 10);
    int m = rnd.next(2, mode == 5 ? 18 : 10);

    vector<string> grid(n, string(m, '.'));

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < 35) grid[i][j] = '#';
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 1) {
                for (int j = 0; j < m; ++j) grid[i][j] = '#';
                int gap = rnd.next(0, m - 1);
                grid[i][gap] = '.';
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < m; ++j) {
            if (j % 2 == 1) {
                for (int i = 0; i < n; ++i) grid[i][j] = '#';
                int gap = (j / 2) % 2 == 0 ? 0 : n - 1;
                if (rnd.next(3) == 0) gap = rnd.next(0, n - 1);
                grid[gap][j] = '.';
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool onBorder = i == 0 || j == 0 || i == n - 1 || j == m - 1;
                bool onMiddle = i == n / 2 || j == m / 2;
                if (!onBorder && !onMiddle && rnd.next(100) < 60) grid[i][j] = '#';
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < 22) grid[i][j] = '#';
            }
        }
        int row = rnd.next(0, n - 1);
        for (int j = 0; j < m; ++j) grid[row][j] = '.';
        int col = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) grid[i][col] = '.';
    }

    vector<pair<int, int>> open;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '#') open.push_back({i, j});
        }
    }

    if ((int)open.size() < 2) {
        grid[0][0] = '.';
        grid[n - 1][m - 1] = '.';
        open = {{0, 0}, {n - 1, m - 1}};
    }

    shuffle(open.begin(), open.end());
    pair<int, int> start = open[0];
    pair<int, int> exit = open[1];
    grid[start.first][start.second] = 'S';
    grid[exit.first][exit.second] = 'E';

    println(n, m);
    for (const string& row : grid) println(row);

    return 0;
}
