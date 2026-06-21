#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n, m;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(5, 14);
    } else if (mode == 2) {
        n = rnd.next(5, 14);
        m = rnd.next(1, 3);
    } else if (mode == 3) {
        n = rnd.next(4, 10);
        m = rnd.next(4, 10);
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }
    if (n * m == 1) {
        m = 2;
    }

    vector<string> grid(n, string(m, '0'));
    int pattern = rnd.next(0, 5);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool land = false;
            if (pattern == 0) {
                land = true;
            } else if (pattern == 1) {
                land = (i == n / 2 || j == m / 2);
            } else if (pattern == 2) {
                land = ((i + j) % 2 == 0);
            } else if (pattern == 3) {
                land = (rnd.next(100) < 65);
            } else if (pattern == 4) {
                land = (i == 0 || i + 1 == n || j == 0 || j + 1 == m || rnd.next(100) < 35);
            } else {
                land = (rnd.next(100) < 25);
            }
            grid[i][j] = land ? '1' : '0';
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    grid[cells[0].first][cells[0].second] = '2';
    grid[cells[1].first][cells[1].second] = '3';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
