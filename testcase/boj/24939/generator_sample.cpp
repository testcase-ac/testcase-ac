#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int direction(long long x, long long y, long long hx, long long hy) {
    if (x < hx && y == hy) return 1;
    if (x > hx && y == hy) return 2;
    if (x == hx && y > hy) return 3;
    if (x == hx && y < hy) return 4;
    if (x < hx && y < hy) return 5;
    if (x > hx && y < hy) return 6;
    if (x < hx && y > hy) return 7;
    if (x > hx && y > hy) return 8;
    return 9;
}

long long pickCoord(long long limit) {
    if (limit <= 20) return rnd.next(1LL, limit);

    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(1LL, min(20LL, limit));
    if (mode == 1) return limit - rnd.next(0LL, min(19LL, limit - 1));
    return rnd.next(1LL, limit);
}

void addQuery(vector<pair<pair<long long, long long>, int>>& queries,
              long long x, long long y, long long hx, long long hy) {
    queries.push_back({{x, y}, direction(x, y, hx, hy)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n, m;
    if (mode == 0) {
        n = rnd.next(1LL, 3LL);
        m = rnd.next(1LL, 3LL);
    } else if (mode == 4) {
        n = rnd.any(vector<long long>{1000000000LL, 999999937LL, rnd.next(1000000LL, 1000000000LL)});
        m = rnd.any(vector<long long>{1000000000LL, 999999929LL, rnd.next(1000000LL, 1000000000LL)});
    } else {
        n = rnd.next(2LL, 30LL);
        m = rnd.next(2LL, 30LL);
    }

    long long hx = pickCoord(n);
    long long hy = pickCoord(m);
    vector<pair<pair<long long, long long>, int>> queries;

    if (mode == 0) {
        addQuery(queries, hx, hy, hx, hy);
    } else if (mode == 1) {
        int q = rnd.next(2, 8);
        for (int i = 0; i < q; ++i) {
            long long x = pickCoord(n);
            addQuery(queries, x, hy, hx, hy);
        }
    } else if (mode == 2) {
        int q = rnd.next(2, 8);
        for (int i = 0; i < q; ++i) {
            long long y = pickCoord(m);
            addQuery(queries, hx, y, hx, hy);
        }
    } else if (mode == 3) {
        vector<pair<long long, long long>> corners = {
            {1, 1}, {1, m}, {n, 1}, {n, m}, {hx, hy}
        };
        shuffle(corners.begin(), corners.end());
        int q = rnd.next(2, (int)corners.size());
        for (int i = 0; i < q; ++i) addQuery(queries, corners[i].first, corners[i].second, hx, hy);
    } else {
        int q = rnd.next(4, 12);
        for (int i = 0; i < q; ++i) {
            long long x = pickCoord(n);
            long long y = pickCoord(m);
            addQuery(queries, x, y, hx, hy);
        }
        if (rnd.next(0, 3) == 0) addQuery(queries, hx, hy, hx, hy);
    }

    println(n, m);
    println((int)queries.size());
    for (auto query : queries) {
        println(query.first.first, query.first.second, query.second);
    }

    return 0;
}
