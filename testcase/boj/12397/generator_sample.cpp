#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> solvableChain(int n) {
    vector<pair<int, int>> levels;
    for (int i = 0; i < n; ++i) {
        int b = rnd.next(i, i + 2);
        int a = rnd.next(0, b);
        levels.emplace_back(a, b);
    }
    return levels;
}

vector<pair<int, int>> randomSmall(int n) {
    int limit = rnd.next(0, 2 * n + 4);
    vector<pair<int, int>> levels;
    for (int i = 0; i < n; ++i) {
        int a = rnd.next(0, limit);
        int b = rnd.next(a, limit + rnd.next(0, 3));
        levels.emplace_back(a, min(b, 2001));
    }
    return levels;
}

vector<pair<int, int>> impossibleGate(int n) {
    vector<pair<int, int>> levels;
    int gate = rnd.next(1, min(2001, n + 4));
    for (int i = 0; i < n; ++i) {
        int a = rnd.next(gate, min(2001, gate + n));
        int b = rnd.next(a, 2001);
        levels.emplace_back(a, b);
    }
    return levels;
}

vector<pair<int, int>> highThresholds(int n) {
    vector<pair<int, int>> levels;
    for (int i = 0; i < n; ++i) {
        int a = rnd.next(0, 2001);
        int b = rnd.next(a, 2001);
        if (rnd.next(3) == 0) b = 2001;
        levels.emplace_back(a, b);
    }
    return levels;
}

vector<pair<int, int>> mixedTrap(int n) {
    vector<pair<int, int>> levels;
    for (int i = 0; i < n; ++i) {
        if (i % 3 == 0) {
            levels.emplace_back(0, rnd.next(1, min(2001, n + 2)));
        } else if (i % 3 == 1) {
            int b = rnd.next(i, min(2001, i + n));
            levels.emplace_back(rnd.next(0, b), b);
        } else {
            int b = rnd.next(n, min(2001, 2 * n + 5));
            levels.emplace_back(rnd.next(0, min(b, n / 2 + 1)), b);
        }
    }
    return levels;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 12);
        if (tc == t - 1 && rnd.next(4) == 0) n = rnd.next(20, 40);

        vector<pair<int, int>> levels;
        int mode = rnd.next(5);
        if (mode == 0) {
            levels = solvableChain(n);
        } else if (mode == 1) {
            levels.assign(n, {0, 0});
        } else if (mode == 2) {
            levels = impossibleGate(n);
        } else if (mode == 3) {
            levels = highThresholds(n);
        } else {
            levels = mixedTrap(n);
        }

        if (rnd.next(2) == 0) {
            shuffle(levels.begin(), levels.end());
        }

        println(n);
        for (const auto& level : levels) {
            println(level.first, level.second);
        }
    }

    return 0;
}
