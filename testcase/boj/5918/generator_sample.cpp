#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static vector<int> chooseCowPositions(int n, int m, int mode) {
    set<int> used;

    if (mode == 0) {
        int start = rnd.next(1, m - n + 1);
        for (int i = 0; i < n; ++i) used.insert(start + i);
    } else if (mode == 1) {
        used.insert(1);
        if (n > 1) used.insert(m);
        int span = min(m, max(n, rnd.next(n, min(m, n + 8))));
        while ((int)used.size() < n) {
            if (rnd.next(2) == 0)
                used.insert(rnd.next(1, span));
            else
                used.insert(rnd.next(m - span + 1, m));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int x = 1 + i * (m - 1) / max(1, n - 1);
            used.insert(x);
        }
        while ((int)used.size() < n) used.insert(rnd.next(1, m));
    } else {
        while ((int)used.size() < n) used.insert(rnd.next(1, m));
    }

    vector<int> cows(used.begin(), used.end());
    shuffle(cows.begin(), cows.end());
    return cows;
}

static vector<int> chooseCosts(int m, int mode) {
    vector<int> costs(m);

    if (mode == 0) {
        int base = rnd.next(1, 20);
        int step = rnd.next(0, 8);
        for (int w = 1; w <= m; ++w) costs[w - 1] = base + step * w + rnd.next(0, 5);
    } else if (mode == 1) {
        int high = rnd.next(20, 80);
        for (int w = 1; w <= m; ++w) costs[w - 1] = max(1, high - w * rnd.next(1, 4) + rnd.next(0, 6));
    } else if (mode == 2) {
        int cheapWidth = rnd.next(1, m);
        for (int w = 1; w <= m; ++w) {
            int distance = abs(w - cheapWidth);
            costs[w - 1] = 1 + distance * rnd.next(1, 5) + rnd.next(0, 12);
        }
    } else {
        for (int w = 1; w <= m; ++w) costs[w - 1] = rnd.next(1, 100);
        costs[rnd.next(0, m - 1)] = rnd.next(1, 3);
    }

    return costs;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(1, 35);
    int n = rnd.next(1, min(14, m));
    int positionMode = rnd.next(0, 3);
    int costMode = rnd.next(0, 3);

    vector<int> cows = chooseCowPositions(n, m, positionMode);
    vector<int> costs = chooseCosts(m, costMode);

    println(n, m);
    for (int x : cows) println(x);
    for (int c : costs) println(c);

    return 0;
}
