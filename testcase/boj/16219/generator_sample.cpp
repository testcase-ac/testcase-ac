#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(5, 30);
    }

    vector<int> s(n);
    iota(s.begin(), s.end(), 0);

    if (mode == 1) {
        reverse(s.begin(), s.end());
    } else if (mode == 2) {
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(n);
            int y = rnd.next(n);
            swap(s[x], s[y]);
        }
    } else if (mode == 4) {
        rotate(s.begin(), s.begin() + rnd.next(n), s.end());
    } else if (mode == 5) {
        reverse(s.begin(), s.end());
        if (n > 2) {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            reverse(s.begin() + l, s.begin() + r + 1);
        }
    }

    int m = rnd.next(1, min(120, max(1, 4 * n)));
    vector<pair<int, int>> queries;
    queries.reserve(m);

    for (int i = 0; i < m; ++i) {
        int pattern = rnd.next(5);
        int x = 0;
        int y = 0;

        if (pattern == 0) {
            x = y = rnd.next(n);
        } else if (pattern == 1 && n > 1) {
            x = rnd.next(n - 1);
            y = x + 1;
        } else if (pattern == 2 && n > 1) {
            x = rnd.next(n);
            y = n - 1 - x;
        } else if (pattern == 3 && !queries.empty()) {
            tie(x, y) = rnd.any(queries);
        } else {
            x = rnd.next(n);
            y = rnd.next(n);
        }

        if (rnd.next(2)) {
            swap(x, y);
        }
        queries.emplace_back(x, y);
    }

    println(n);
    println(s);
    println(m);
    for (auto [x, y] : queries) {
        println(x, y);
    }

    return 0;
}
