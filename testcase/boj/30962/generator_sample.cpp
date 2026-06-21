#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Query = vector<int>;

Query makeQuery(int x1, int y1, int x2, int y2, int w) {
    if (1LL * x1 * y2 - 1LL * y1 * x2 >= 0) {
        swap(x1, x2);
        swap(y1, y2);
    }
    return {x1, y1, x2, y2, w};
}

int randomWeight() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        vector<int> small = {1, 2, 4, 5, 8, 9, 10, 13, 16, 17, 25, 50, 65, 100};
        return rnd.any(small);
    }
    if (mode == 1) {
        int a = rnd.next(1, 316);
        int b = rnd.next(0, 316);
        int w = a * a + b * b;
        return min(w, 100000);
    }
    if (mode == 2) {
        return rnd.next(1, 200);
    }
    return rnd.next(90000, 100000);
}

Query randomSmallQuery() {
    int x1 = rnd.next(1, 30);
    int y1 = rnd.next(1, 30);
    int x2 = rnd.next(1, 30);
    int y2 = rnd.next(1, 30);
    while (1LL * x1 * y2 == 1LL * y1 * x2) {
        x2 = rnd.next(1, 30);
        y2 = rnd.next(1, 30);
    }
    return makeQuery(x1, y1, x2, y2, randomWeight());
}

Query narrowAngleQuery() {
    int x = rnd.next(1, 100000);
    int y = rnd.next(1, 100000);
    int dx = rnd.next(0, 3);
    int dy = rnd.next(0, 3);
    int x2 = min(100000, x + dx);
    int y2 = min(100000, y + dy);
    if (x2 == x && y2 == y) {
        if (x < 100000) ++x2;
        else --x2;
    }
    while (1LL * x * y2 == 1LL * y * x2) {
        if (y2 > 1) --y2;
        else ++x2;
    }
    return makeQuery(x, y, x2, y2, randomWeight());
}

Query wideAngleQuery() {
    int low = rnd.next(1, 5);
    int high = rnd.next(50000, 100000);
    if (rnd.next(0, 1) == 0) {
        return makeQuery(low, high, high, low, randomWeight());
    }
    return makeQuery(rnd.next(1, 100), 100000, 100000, rnd.next(1, 100), randomWeight());
}

Query boundaryQuery() {
    vector<pair<int, int>> points = {
        {1, 100000},
        {100000, 1},
        {99999, 100000},
        {100000, 99999},
        {1, 1},
        {316, 1},
        {1, 316},
    };
    auto a = rnd.any(points);
    auto b = rnd.any(points);
    while (1LL * a.first * b.second == 1LL * a.second * b.first) {
        b = rnd.any(points);
    }
    return makeQuery(a.first, a.second, b.first, b.second, randomWeight());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = mode == 4 ? rnd.next(20, 50) : rnd.next(1, 20);
    vector<Query> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        int kind = rnd.next(0, 99);
        if (kind < 35) {
            queries.push_back(randomSmallQuery());
        } else if (kind < 60) {
            queries.push_back(narrowAngleQuery());
        } else if (kind < 85) {
            queries.push_back(wideAngleQuery());
        } else {
            queries.push_back(boundaryQuery());
        }
    }

    println(q);
    for (const auto& query : queries) {
        println(query);
    }

    return 0;
}
