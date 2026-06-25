#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<int> x(n + 1);

    if (mode == 0) {
        n = 2;
        x[1] = rnd.next(1, 20);
        x[2] = rnd.next(1, 20);
    } else if (mode == 1) {
        int base = rnd.next(1, 8);
        for (int i = 1; i <= n; ++i) x[i] = base;
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) x[i] = rnd.next(1, 30);
        x[rnd.next(1, n)] = 1000000000;
    } else {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(1000000000, lo + rnd.next(0, 50)));
        for (int i = 1; i <= n; ++i) x[i] = rnd.next(lo, hi);
    }

    vector<pair<int, int>> candidates;
    if (mode == 3) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) candidates.emplace_back(center, i);
        }
    } else if (mode == 4) {
        for (int i = 1; i < n; ++i) candidates.emplace_back(i, i + 1);
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) candidates.emplace_back(i, j);
        }
    }

    shuffle(candidates.begin(), candidates.end());

    int baseCount = rnd.next(1, static_cast<int>(candidates.size()));
    vector<pair<int, int>> queries;
    for (int i = 0; i < baseCount; ++i) {
        auto [a, b] = candidates[i];
        if (rnd.next(0, 1)) swap(a, b);
        queries.emplace_back(a, b);

        if (rnd.next(0, 4) == 0) {
            if (rnd.next(0, 1)) swap(a, b);
            queries.emplace_back(a, b);
        }
    }

    while (static_cast<int>(queries.size()) > 60) {
        queries.pop_back();
    }

    println(n, static_cast<int>(queries.size()));
    for (auto [a, b] : queries) {
        println(a, b, min(x[a], x[b]));
    }

    return 0;
}
