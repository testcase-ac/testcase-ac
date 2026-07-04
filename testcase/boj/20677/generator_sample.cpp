#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    if (mode == 1) {
        m = rnd.next(1, 3);
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        m = rnd.next(1, 12);
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        m = rnd.next(3, 8);
        n = rnd.next(2, 8);
    }

    vector<string> grid(m, string(n, '.'));

    vector<pair<int, int>> cells;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> s = cells[0];
    pair<int, int> e = cells.size() == 1 ? cells[0] : cells[1];
    if (cells.size() == 1) {
        n = 2;
        grid.assign(1, "..");
        cells = {{0, 0}, {0, 1}};
        s = cells[0];
        e = cells[1];
    }

    double seatProb = 0.0;
    if (mode == 0) {
        seatProb = rnd.next(0.0, 0.20);
    } else if (mode == 1 || mode == 2) {
        seatProb = rnd.next(0.0, 0.35);
    } else if (mode == 3) {
        seatProb = rnd.next(0.35, 0.70);
    } else if (mode == 5) {
        seatProb = rnd.next(0.15, 0.40);
    }

    for (const auto& cell : cells) {
        int r = cell.first;
        int c = cell.second;
        if ((r == s.first && c == s.second) || (r == e.first && c == e.second)) {
            continue;
        }
        if (rnd.next() < seatProb) {
            grid[r][c] = '#';
        }
    }

    if (mode == 4) {
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = '.';
            }
        }
    }

    if (mode == 5) {
        int barrierRow = rnd.next(1, m - 2);
        for (int c = 0; c < n; ++c) {
            grid[barrierRow][c] = '#';
        }
        s = {rnd.next(0, barrierRow - 1), rnd.next(0, n - 1)};
        e = {rnd.next(barrierRow + 1, m - 1), rnd.next(0, n - 1)};
        grid[s.first][s.second] = '.';
        grid[e.first][e.second] = '.';
    }

    int patientCount = 0;
    if (mode != 4) {
        int freeCount = 0;
        for (const auto& cell : cells) {
            int r = cell.first;
            int c = cell.second;
            if (grid[r][c] == '.' &&
                !(r == s.first && c == s.second) &&
                !(r == e.first && c == e.second)) {
                ++freeCount;
            }
        }
        if (freeCount > 0) {
            int cap = min(freeCount, max(1, (m * n) / rnd.next(3, 8)));
            patientCount = rnd.next(1, cap);
        }
    }

    shuffle(cells.begin(), cells.end());
    for (const auto& cell : cells) {
        int r = cell.first;
        int c = cell.second;
        if (patientCount == 0) {
            break;
        }
        if (grid[r][c] == '.' &&
            !(r == s.first && c == s.second) &&
            !(r == e.first && c == e.second)) {
            grid[r][c] = '*';
            --patientCount;
        }
    }

    grid[s.first][s.second] = 'S';
    grid[e.first][e.second] = 'E';

    println(m, n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
