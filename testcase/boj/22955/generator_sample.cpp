#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 16 : 10);
    int m = rnd.next(2, mode == 5 ? 18 : 12);

    vector<string> grid(n, string(m, 'F'));

    double dog_prob = 0.06;
    double ladder_prob = 0.12;
    double hole_prob = 0.08;

    if (mode == 1) {
        dog_prob = 0.18;
        ladder_prob = 0.08;
        hole_prob = 0.04;
    } else if (mode == 2) {
        dog_prob = 0.04;
        ladder_prob = 0.28;
        hole_prob = 0.06;
    } else if (mode == 3) {
        dog_prob = 0.06;
        ladder_prob = 0.16;
        hole_prob = 0.22;
    } else if (mode == 4) {
        dog_prob = 0.14;
        ladder_prob = 0.22;
        hole_prob = 0.18;
    } else if (mode == 5) {
        dog_prob = 0.10;
        ladder_prob = 0.20;
        hole_prob = 0.16;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double x = rnd.next();
            if (i + 1 != n && x < hole_prob) {
                grid[i][j] = 'X';
            } else if (x < hole_prob + ladder_prob) {
                grid[i][j] = 'L';
            } else if (x < hole_prob + ladder_prob + dog_prob) {
                grid[i][j] = 'D';
            }
        }
    }

    if (mode == 3 || mode == 4) {
        int columns = rnd.next(1, max(1, m / 3));
        for (int c = 0; c < columns; ++c) {
            int j = rnd.next(0, m - 1);
            int top = rnd.next(0, n - 2);
            int bottom = rnd.next(top, n - 2);
            for (int i = top; i <= bottom; ++i) {
                grid[i][j] = 'X';
            }
            if (top > 0 && rnd.next(0, 1)) {
                grid[top - 1][j] = 'L';
            }
            grid[n - 1][j] = rnd.next(0, 1) ? 'F' : 'L';
        }
    }

    if (mode == 1 || mode == 4) {
        int walls = rnd.next(1, max(1, n / 3));
        for (int w = 0; w < walls; ++w) {
            int i = rnd.next(0, n - 1);
            int gap = rnd.next(0, m - 1);
            for (int j = 0; j < m; ++j) {
                if (j != gap && rnd.next(0, 3) != 0) {
                    grid[i][j] = 'D';
                }
            }
        }
    }

    if (mode == 2 || mode == 4 || mode == 5) {
        int ladders = rnd.next(1, max(1, m / 2));
        for (int k = 0; k < ladders; ++k) {
            int j = rnd.next(0, m - 1);
            int top = rnd.next(0, n - 2);
            int bottom = rnd.next(top + 1, n - 1);
            for (int i = top; i <= bottom; ++i) {
                if (grid[i][j] != 'X') {
                    grid[i][j] = 'L';
                }
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != 'D' && grid[i][j] != 'X') {
                cells.push_back({i, j});
            }
        }
    }

    if ((int)cells.size() < 2) {
        grid[n - 1][0] = 'F';
        grid[n - 1][m - 1] = 'F';
        cells = {{n - 1, 0}, {n - 1, m - 1}};
    }

    shuffle(cells.begin(), cells.end());
    auto cat = cells[0];
    auto exit = cells[1];

    if (mode == 0 && rnd.next(0, 1)) {
        cat = {n - 1, rnd.next(0, m - 1)};
        exit = {rnd.next(0, n - 1), rnd.next(0, m - 1)};
        if (cat == exit) {
            exit.second = (exit.second + 1) % m;
        }
        grid[cat.first][cat.second] = 'F';
        grid[exit.first][exit.second] = 'F';
    }

    grid[cat.first][cat.second] = 'C';
    grid[exit.first][exit.second] = 'E';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
