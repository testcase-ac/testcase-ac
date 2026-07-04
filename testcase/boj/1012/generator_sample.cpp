#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

struct CaseData {
    int m;
    int n;
    vector<Cell> cells;
};

vector<Cell> allCells(int m, int n) {
    vector<Cell> cells;
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
            cells.push_back({x, y});
        }
    }
    return cells;
}

CaseData randomSparse() {
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    vector<Cell> cells = allCells(m, n);
    shuffle(cells.begin(), cells.end());
    cells.resize(rnd.next(1, min<int>(cells.size(), 18)));
    return {m, n, cells};
}

CaseData connectedBlob() {
    int m = rnd.next(2, 12);
    int n = rnd.next(2, 12);
    int target = rnd.next(1, min(m * n, 22));

    set<Cell> used;
    vector<Cell> frontier;
    Cell start = {rnd.next(0, m - 1), rnd.next(0, n - 1)};
    used.insert(start);
    frontier.push_back(start);

    while ((int)used.size() < target && !frontier.empty()) {
        Cell cur = rnd.any(frontier);
        vector<Cell> next = {
            {cur.first + 1, cur.second},
            {cur.first - 1, cur.second},
            {cur.first, cur.second + 1},
            {cur.first, cur.second - 1},
        };
        shuffle(next.begin(), next.end());

        bool expanded = false;
        for (Cell cand : next) {
            if (0 <= cand.first && cand.first < m && 0 <= cand.second && cand.second < n &&
                !used.count(cand)) {
                used.insert(cand);
                frontier.push_back(cand);
                expanded = true;
                break;
            }
        }

        if (!expanded) {
            frontier.erase(find(frontier.begin(), frontier.end(), cur));
        }
    }

    vector<Cell> cells(used.begin(), used.end());
    return {m, n, cells};
}

CaseData isolatedCheckerboard() {
    int m = rnd.next(3, 13);
    int n = rnd.next(3, 13);
    vector<Cell> candidates;
    int parity = rnd.next(0, 1);
    for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
            if ((x + y) % 2 == parity) {
                candidates.push_back({x, y});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(rnd.next(1, min<int>(candidates.size(), 24)));
    return {m, n, candidates};
}

CaseData snakePath() {
    int m = rnd.next(2, 10);
    int n = rnd.next(2, 10);
    vector<Cell> path;
    for (int y = 0; y < n; ++y) {
        if (y % 2 == 0) {
            for (int x = 0; x < m; ++x) {
                path.push_back({x, y});
            }
        } else {
            for (int x = m - 1; x >= 0; --x) {
                path.push_back({x, y});
            }
        }
    }

    int length = rnd.next(1, min<int>(path.size(), 30));
    int start = rnd.next(0, (int)path.size() - length);
    vector<Cell> cells(path.begin() + start, path.begin() + start + length);
    return {m, n, cells};
}

CaseData denseSmallField() {
    int m = rnd.next(1, 7);
    int n = rnd.next(1, 7);
    vector<Cell> cells = allCells(m, n);
    shuffle(cells.begin(), cells.end());
    int minK = max(1, (m * n + 1) / 2);
    cells.resize(rnd.next(minK, m * n));
    return {m, n, cells};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        CaseData cur;
        if (mode == 0) {
            cur = randomSparse();
        } else if (mode == 1) {
            cur = connectedBlob();
        } else if (mode == 2) {
            cur = isolatedCheckerboard();
        } else if (mode == 3) {
            cur = snakePath();
        } else {
            cur = denseSmallField();
        }

        shuffle(cur.cells.begin(), cur.cells.end());
        println(cur.m, cur.n, (int)cur.cells.size());
        for (Cell cell : cur.cells) {
            println(cell.first, cell.second);
        }
    }

    return 0;
}
