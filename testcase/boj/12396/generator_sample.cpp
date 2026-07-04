#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> makeCase(int mode) {
    int n = rnd.next(1, 10);
    vector<pair<int, int>> levels;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(0, min(2 * n, 12));
            int a = rnd.next(0, b);
            levels.push_back({a, b});
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, i);
            int b = rnd.next(i, min(2 * n - 1, i + 3));
            levels.push_back({a, b});
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, min(i, 2));
            int b = rnd.next(max(a, 2 * n + rnd.next(0, 3)), 2001);
            levels.push_back({a, b});
        }
    } else if (mode == 3) {
        int base = rnd.next(0, min(6, 2 * n));
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, base);
            int b = rnd.next(a, min(2001, base + rnd.next(0, 5)));
            levels.push_back({a, b});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(1996, 2001);
            int a = rnd.next(max(0, b - 5), b);
            if (rnd.next(3) == 0) a = 0;
            levels.push_back({a, b});
        }
    }

    shuffle(levels.begin(), levels.end());
    return levels;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        vector<pair<int, int>> levels = makeCase(caseIndex % 5);
        println(static_cast<int>(levels.size()));
        for (const auto& level : levels) {
            println(level.first, level.second);
        }
    }

    return 0;
}
