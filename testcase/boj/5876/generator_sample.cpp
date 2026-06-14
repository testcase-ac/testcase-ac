#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 5);
    vector<string> grid(n, string(n, '('));
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next(0, 3) == 0 ? '(' : ')';
            }
        }
        grid[0][0] = ')';
    } else if (mode == 1) {
        char fill = rnd.next(0, 1) == 0 ? '(' : ')';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = fill;
            }
        }
    } else if (mode == 2) {
        int split = rnd.next(1, 2 * n - 2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = i + j < split ? '(' : ')';
            }
        }
        grid[0][0] = '(';
    } else if (mode == 3) {
        vector<pair<int, int>> path;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < n; ++j) path.push_back({i, j});
            } else {
                for (int j = n - 1; j >= 0; --j) path.push_back({i, j});
            }
        }

        int maxEven = (int)path.size();
        if (maxEven % 2 == 1) --maxEven;
        int length = 2 * rnd.next(1, maxEven / 2);
        int half = length / 2;
        for (int k = 0; k < (int)path.size(); ++k) {
            int r = path[k].first;
            int c = path[k].second;
            if (k < half) {
                grid[r][c] = '(';
            } else if (k < length) {
                grid[r][c] = ')';
            } else {
                grid[r][c] = rnd.next(0, 1) == 0 ? '(' : ')';
            }
        }
    } else {
        double closeProbability = rnd.next(0.20, 0.80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next() < closeProbability ? ')' : '(';
            }
        }
        grid[0][0] = '(';
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
