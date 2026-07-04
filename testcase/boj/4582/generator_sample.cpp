#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Pattern {
    int k;
    int x;
    int y;
    int s;
    int t;
};

static bool tryAddPattern(vector<Pattern>& patterns, set<pair<int, int>>& used,
                          int n, int k, int x, int y, int s, int t) {
    if (k == 1) {
        s = 0;
        t = 0;
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < k; ++i) {
        int px = x + i * s;
        int py = y + i * t;
        if (px < 1 || px > n || py < 1 || py > n) return false;
        if (used.count({px, py})) return false;
        cells.push_back({px, py});
    }

    for (auto cell : cells) used.insert(cell);
    patterns.push_back({k, x, y, s, t});
    return true;
}

static void addRandomLine(vector<Pattern>& patterns, set<pair<int, int>>& used,
                          int n, int remaining) {
    const vector<pair<int, int>> steps = {
        {1, 0}, {0, 1}, {1, 1}, {1, -1}, {2, 1}, {1, 2}, {2, -1}
    };

    for (int attempt = 0; attempt < 200; ++attempt) {
        auto step = rnd.any(steps);
        if (rnd.next(2) == 1) {
            step.first = -step.first;
            step.second = -step.second;
        }

        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        int maxK = 1;
        int px = x;
        int py = y;
        while (maxK < remaining) {
            px += step.first;
            py += step.second;
            if (px < 1 || px > n || py < 1 || py > n) break;
            ++maxK;
        }

        int k = rnd.next(1, maxK);
        if (tryAddPattern(patterns, used, n, k, x, y, step.first, step.second)) return;
    }
}

static vector<Pattern> makeDataset(int n, int targetQueens) {
    vector<Pattern> patterns;
    set<pair<int, int>> used;

    while ((int)used.size() < targetQueens && (int)patterns.size() < 249) {
        int remaining = targetQueens - (int)used.size();
        if (remaining == 1 || rnd.next(100) < 35) {
            for (int attempt = 0; attempt < 200; ++attempt) {
                int x = rnd.next(1, n);
                int y = rnd.next(1, n);
                if (tryAddPattern(patterns, used, n, 1, x, y, 0, 0)) break;
            }
        } else {
            addRandomLine(patterns, used, n, remaining);
        }
    }

    return patterns;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(3, 7);
    for (int dataset = 0; dataset < datasets; ++dataset) {
        int n;
        if (dataset == 0) {
            n = 1;
        } else if (dataset == 1) {
            n = rnd.next(4, 8);
        } else {
            n = rnd.next(8, 30);
        }

        int targetQueens = dataset == 0 ? 1 : rnd.next(1, min(n, 18));
        vector<Pattern> patterns = makeDataset(n, targetQueens);
        shuffle(patterns.begin(), patterns.end());

        println(n, (int)patterns.size());
        for (const Pattern& pattern : patterns) {
            println(pattern.k, pattern.x, pattern.y, pattern.s, pattern.t);
        }
    }

    println(0);
    return 0;
}
