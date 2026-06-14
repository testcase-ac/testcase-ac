#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int clampInt(long long value, int lo, int hi) {
    return (int)max<long long>(lo, min<long long>(hi, value));
}

int uniqueNear(set<int>& used, int base, int radius) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int value = clampInt((long long)base + rnd.next(-radius, radius), 1, 1000000000);
        if (used.insert(value).second) return value;
    }
    for (int value = 1; value <= 1000000000; ++value) {
        if (used.insert(value).second) return value;
    }
    return 1;
}

pair<int, int> makeRangeAround(int center, int maxWidth) {
    int leftSlack = rnd.next(0, maxWidth);
    int rightSlack = rnd.next(0, maxWidth - leftSlack);
    int u = clampInt((long long)center - leftSlack, 1, 1000000000);
    int v = clampInt((long long)center + rightSlack, 1, 1000000000);
    if (v - u > 10000) v = u + 10000;
    if (v > 1000000000) {
        v = 1000000000;
        u = max(1, v - 10000);
    }
    return {u, v};
}

pair<int, int> makeWindow(int lo, int hi) {
    int width = rnd.next(0, min(10000, hi - lo));
    int start = rnd.next(lo, hi - width);
    return {start, start + width};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 28);
    int q = rnd.next(1, 24);

    vector<int> centers = {1, 5000, 10000, 20000, 999990000, 1000000000};
    if (rnd.next(2)) centers.push_back(rnd.next(1, 1000000000));

    set<int> usedA;
    set<int> usedB;
    vector<pair<int, int>> menus;
    for (int i = 0; i < n; ++i) {
        int aCenter = rnd.any(centers);
        int bCenter = rnd.any(centers);
        int radius = rnd.next(0, 10000);
        int a = uniqueNear(usedA, aCenter, radius);
        int b = uniqueNear(usedB, bCenter, radius);
        menus.push_back({a, b});
    }
    shuffle(menus.begin(), menus.end());

    vector<tuple<int, int, int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 5);
        int u, v, x, y;

        if (mode <= 2) {
            auto menu = rnd.any(menus);
            tie(u, v) = makeRangeAround(menu.first, rnd.next(0, 10000));
            tie(x, y) = makeRangeAround(menu.second, rnd.next(0, 10000));
        } else if (mode == 3) {
            tie(u, v) = makeWindow(1, 10001);
            tie(x, y) = makeWindow(1, 10001);
        } else if (mode == 4) {
            tie(u, v) = makeWindow(999990000, 1000000000);
            tie(x, y) = makeWindow(999990000, 1000000000);
        } else {
            int baseA = rnd.any(centers);
            int baseB = rnd.any(centers);
            tie(u, v) = makeRangeAround(baseA, rnd.next(0, 10000));
            tie(x, y) = makeRangeAround(baseB, rnd.next(0, 10000));
        }

        queries.push_back({u, v, x, y});
    }

    println(n, q);
    for (auto menu : menus) println(menu.first, menu.second);
    for (auto query : queries) {
        int u, v, x, y;
        tie(u, v, x, y) = query;
        println(u, v, x, y);
    }

    return 0;
}
