#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(4, 12);
    int h;
    int d;

    vector<string> grid(n, string(n, '.'));
    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start;
    pair<int, int> finish;
    if (mode == 0) {
        start = {0, 0};
        finish = {n - 1, n - 1};
    } else if (mode == 1) {
        start = {rnd.next(0, n - 1), rnd.next(0, n - 1)};
        do {
            finish = {rnd.next(0, n - 1), rnd.next(0, n - 1)};
        } while (finish == start);
    } else if (mode == 2) {
        start = {rnd.next(0, 1) * (n - 1), rnd.next(0, n - 1)};
        finish = {n - 1 - start.first, rnd.next(0, n - 1)};
    } else {
        start = cells[0];
        finish = cells[1];
    }

    grid[start.first][start.second] = 'S';
    grid[finish.first][finish.second] = 'E';

    int maxUmbrellas = min(10, n * n - 2);
    int umbrellaCount;
    if (mode == 3) {
        umbrellaCount = rnd.next(7, maxUmbrellas);
    } else if (mode == 4) {
        umbrellaCount = rnd.next(0, min(2, maxUmbrellas));
    } else {
        umbrellaCount = rnd.next(0, maxUmbrellas);
    }

    vector<pair<int, int>> candidates;
    if (mode == 2) {
        int r = start.first;
        int c = start.second;
        while (r != finish.first || c != finish.second) {
            if (r != finish.first) {
                r += (finish.first > r ? 1 : -1);
            } else if (c != finish.second) {
                c += (finish.second > c ? 1 : -1);
            }
            if (make_pair(r, c) != finish) {
                candidates.push_back({r, c});
            }
        }
        shuffle(candidates.begin(), candidates.end());
    }

    for (auto cell : cells) {
        if ((int)candidates.size() >= maxUmbrellas) {
            break;
        }
        if (cell != start && cell != finish) {
            candidates.push_back(cell);
        }
    }

    int placed = 0;
    for (auto cell : candidates) {
        if (placed == umbrellaCount) {
            break;
        }
        if (grid[cell.first][cell.second] == '.') {
            grid[cell.first][cell.second] = 'U';
            ++placed;
        }
    }

    int distance = abs(start.first - finish.first) + abs(start.second - finish.second);
    if (mode == 0) {
        h = rnd.next(1, max(1, distance - 1));
        d = rnd.next(1, 5);
    } else if (mode == 1) {
        h = rnd.next(1, min(10000, distance + 3));
        d = rnd.next(1, 8);
    } else if (mode == 4) {
        h = rnd.next(max(1, distance), min(10000, distance + 20));
        d = rnd.next(1, 5000);
    } else {
        h = rnd.next(1, 20);
        d = rnd.next(1, 15);
    }

    println(n, h, d);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
