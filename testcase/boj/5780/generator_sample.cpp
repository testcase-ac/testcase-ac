#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static vector<Cell> complementPonds(int n, int m, const set<Cell>& land) {
    vector<Cell> ponds;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            if (!land.count({r, c})) {
                ponds.push_back({r, c});
            }
        }
    }
    shuffle(ponds.begin(), ponds.end());
    return ponds;
}

static void addLineCase(vector<pair<pair<int, int>, set<Cell>>>& cases) {
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 14);
    if (rnd.next(2) == 0) {
        n = 1;
    } else {
        m = 1;
    }

    set<Cell> land;
    int keep = rnd.next(1, n * m);
    vector<Cell> cells;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < keep; ++i) {
        land.insert(cells[i]);
    }
    cases.push_back({{n, m}, land});
}

static void addDenseRectangleCase(vector<pair<pair<int, int>, set<Cell>>>& cases) {
    int n = rnd.next(2, 7);
    int m = rnd.next(2, 7);
    set<Cell> land;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            land.insert({r, c});
        }
    }

    int holes = rnd.next(0, min(8, n * m - 1));
    vector<Cell> cells(land.begin(), land.end());
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < holes; ++i) {
        land.erase(cells[i]);
    }
    cases.push_back({{n, m}, land});
}

static void addCheckerCase(vector<pair<pair<int, int>, set<Cell>>>& cases) {
    int n = rnd.next(3, 8);
    int m = rnd.next(3, 8);
    set<Cell> land;
    int parity = rnd.next(2);
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            if ((r + c) % 2 == parity || rnd.next(4) == 0) {
                land.insert({r, c});
            }
        }
    }

    while ((int)land.size() > 50) {
        auto it = land.begin();
        advance(it, rnd.next((int)land.size()));
        land.erase(it);
    }
    if (land.empty()) {
        land.insert({rnd.next(1, n), rnd.next(1, m)});
    }
    cases.push_back({{n, m}, land});
}

static void addIslandCase(vector<pair<pair<int, int>, set<Cell>>>& cases) {
    int n = rnd.next(6, 10);
    int m = rnd.next(6, 10);
    set<Cell> land;
    int blocks = rnd.next(2, 5);
    for (int b = 0; b < blocks; ++b) {
        int h = rnd.next(1, 3);
        int w = rnd.next(1, 3);
        int r0 = rnd.next(1, n - h + 1);
        int c0 = rnd.next(1, m - w + 1);
        for (int r = r0; r < r0 + h; ++r) {
            for (int c = c0; c < c0 + w; ++c) {
                land.insert({r, c});
            }
        }
    }

    if (land.empty()) {
        land.insert({1, 1});
    }
    cases.push_back({{n, m}, land});
}

static void addSparseCase(vector<pair<pair<int, int>, set<Cell>>>& cases) {
    int n = rnd.next(8, 12);
    int m = rnd.next(8, 12);
    int keep = rnd.next(1, 35);
    set<Cell> land;
    while ((int)land.size() < keep) {
        land.insert({rnd.next(1, n), rnd.next(1, m)});
    }
    cases.push_back({{n, m}, land});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<pair<int, int>, set<Cell>>> cases;
    addLineCase(cases);
    addDenseRectangleCase(cases);
    addCheckerCase(cases);
    addIslandCase(cases);
    addSparseCase(cases);

    shuffle(cases.begin(), cases.end());

    for (const auto& tc : cases) {
        int n = tc.first.first;
        int m = tc.first.second;
        vector<Cell> ponds = complementPonds(n, m, tc.second);

        println(n, m);
        println((int)ponds.size());
        for (const auto& pond : ponds) {
            println(pond.first, pond.second);
        }
    }
    println(0, 0);

    return 0;
}
