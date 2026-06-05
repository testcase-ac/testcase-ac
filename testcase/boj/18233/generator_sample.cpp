#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int p = rnd.next(1, n);
    if (mode == 5) {
        n = rnd.next(1, 8);
        p = rnd.next(n + 1, 20);
    } else if (mode == 4) {
        n = rnd.next(13, 20);
        p = rnd.next(1, n);
    }

    vector<pair<int, int>> ranges(n);
    for (int i = 0; i < n; ++i) {
        int x = rnd.next(1, 80);
        int width = rnd.next(0, 120);
        if (mode == 3 && rnd.next(0, 2) == 0) width = 0;
        ranges[i] = {x, x + width};
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    long long low = 0;
    long long high = 0;
    int chosen = min(p, n);
    for (int i = 0; i < chosen; ++i) {
        int idx = order[i];
        low += ranges[idx].first;
        high += ranges[idx].second;
    }

    int e;
    if (mode == 0) {
        e = (int)rnd.next(low, high);
    } else if (mode == 1) {
        e = (int)max(1LL, low - rnd.next(1, 40));
    } else if (mode == 2) {
        e = (int)min(1000000LL, high + rnd.next(1, 200));
    } else if (mode == 5) {
        e = rnd.next(1, 500);
    } else {
        long long base = rnd.next(low, high);
        e = (int)min(1000000LL, max(1LL, base));
    }

    if (rnd.next(0, 4) == 0) {
        int idx = rnd.next(0, n - 1);
        int x = rnd.next(999000, 1000000);
        ranges[idx] = {x, 1000000};
        if (mode == 0) e = rnd.next(1, 1000000);
    }

    println(n, p, e);
    for (auto [x, y] : ranges) println(x, y);

    return 0;
}
