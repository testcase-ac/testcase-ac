#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

int dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    int h = rnd.next(1, 10);

    if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(1, 3);
        h = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        m = rnd.next(7, 10);
        h = rnd.next(7, 10);
    } else if (mode == 3) {
        n = 10;
        m = rnd.next(1, 10);
        h = rnd.next(1, 10);
    } else if (mode == 4) {
        n = rnd.next(5, 10);
        m = rnd.next(2, 6);
        h = rnd.next(2, 6);
    } else if (mode == 5) {
        n = rnd.next(6, 10);
        m = rnd.next(3, 8);
        h = rnd.next(1, 5);
    }

    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> home;
    if (mode == 3) {
        vector<pair<int, int>> corners = {{0, 0}, {0, n - 1}, {n - 1, 0}, {n - 1, n - 1}};
        home = rnd.any(corners);
    } else if (mode == 4 || mode == 5) {
        int lo = max(0, n / 2 - 1);
        int hi = min(n - 1, n / 2 + 1);
        home = {rnd.next(lo, hi), rnd.next(lo, hi)};
    } else {
        home = cells.back();
    }
    board[home.first][home.second] = 1;

    vector<pair<int, int>> candidates;
    for (auto cell : cells) {
        if (cell != home) {
            candidates.push_back(cell);
        }
    }

    vector<pair<int, int>> milks;
    if (mode == 0) {
        int milk_count = rnd.next(0, min(3, (int)candidates.size()));
        milks.assign(candidates.begin(), candidates.begin() + milk_count);
    } else if (mode == 1) {
        vector<pair<int, int>> near_home;
        for (auto cell : candidates) {
            if (dist(home, cell) <= 2) {
                near_home.push_back(cell);
            }
        }
        shuffle(near_home.begin(), near_home.end());
        int milk_count = rnd.next(1, min(10, (int)near_home.size()));
        milks.assign(near_home.begin(), near_home.begin() + milk_count);
    } else if (mode == 2) {
        int milk_count = min(10, (int)candidates.size());
        milks.assign(candidates.begin(), candidates.begin() + milk_count);
    } else if (mode == 3) {
        sort(candidates.begin(), candidates.end(), [&](pair<int, int> a, pair<int, int> b) {
            return dist(home, a) > dist(home, b);
        });
        int milk_count = rnd.next(min(4, (int)candidates.size()), min(10, (int)candidates.size()));
        milks.assign(candidates.begin(), candidates.begin() + milk_count);
    } else if (mode == 4) {
        sort(candidates.begin(), candidates.end(), [&](pair<int, int> a, pair<int, int> b) {
            return dist(home, a) < dist(home, b);
        });
        int milk_count = rnd.next(5, min(10, (int)candidates.size()));
        int prefix = min((int)candidates.size(), max(milk_count, 18));
        vector<pair<int, int>> close_cells(candidates.begin(), candidates.begin() + prefix);
        shuffle(close_cells.begin(), close_cells.end());
        milks.assign(close_cells.begin(), close_cells.begin() + milk_count);
    } else {
        sort(candidates.begin(), candidates.end(), [&](pair<int, int> a, pair<int, int> b) {
            int da = abs(a.first - home.first) + 2 * abs(a.second - home.second);
            int db = abs(b.first - home.first) + 2 * abs(b.second - home.second);
            return da < db;
        });
        int milk_count = rnd.next(6, min(10, (int)candidates.size()));
        int span = min((int)candidates.size(), max(milk_count, 20));
        vector<pair<int, int>> path_cells(candidates.begin(), candidates.begin() + span);
        shuffle(path_cells.begin(), path_cells.end());
        milks.assign(path_cells.begin(), path_cells.begin() + milk_count);
    }

    for (auto milk : milks) {
        board[milk.first][milk.second] = 2;
    }

    println(n, m, h);
    for (int r = 0; r < n; ++r) {
        println(board[r]);
    }

    return 0;
}
