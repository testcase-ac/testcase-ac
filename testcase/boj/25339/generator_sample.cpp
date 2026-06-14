#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

long long clampPos(long long x, long long n) {
    return max(1LL, min(x, n));
}

pair<long long, long long> orderedPair(long long a, long long b, long long n) {
    a = clampPos(a, n);
    b = clampPos(b, n);
    if (a == b) {
        if (b < n) ++b;
        else --a;
    }
    if (a > b) swap(a, b);
    return {a, b};
}

pair<long long, long long> intervalWithLength(long long n, long long len) {
    len = max(2LL, min(len, n));
    long long l = rnd.next(1LL, n - len + 1);
    return {l, l + len - 1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    long long n;
    if (mode == 0) {
        n = rnd.next(2LL, 12LL);
    } else if (mode == 1) {
        n = rnd.next(13LL, 200LL);
    } else if (mode == 2) {
        n = rnd.next(999999900LL, 1000000000LL);
    } else {
        vector<long long> specialN = {2, 3, 4, 5, 1000000000LL};
        n = rnd.any(specialN);
    }

    int q = rnd.next(8, 30);
    if (n == 2) q = rnd.next(1, 12);

    vector<pair<int, pair<long long, long long>>> queries;
    queries.reserve(q);

    vector<long long> reversalLens = {2, 3, 4, 5, 6, n};
    for (int i = 0; i < q; ++i) {
        int pattern = rnd.next(0, 5);
        int a = rnd.next(1, 2);
        long long l, r;

        if (pattern == 0) {
            auto p = orderedPair(1, n, n);
            l = p.first;
            r = p.second;
        } else if (pattern == 1) {
            long long start = rnd.next(1LL, n - 1);
            l = start;
            r = start + 1;
        } else if (pattern == 2) {
            long long center = rnd.next(1LL, n);
            auto p = orderedPair(center - rnd.next(0LL, 3LL), center + rnd.next(0LL, 3LL), n);
            l = p.first;
            r = p.second;
        } else if (pattern == 3) {
            long long len = rnd.any(reversalLens);
            auto p = intervalWithLength(n, len);
            l = p.first;
            r = p.second;
            a = 2;
        } else if (pattern == 4 && n > 10) {
            long long edge = rnd.next(0, 1) ? n : 1;
            long long other = edge == 1 ? rnd.next(2LL, min(n, 10LL)) : rnd.next(max(1LL, n - 9), n - 1);
            auto p = orderedPair(edge, other, n);
            l = p.first;
            r = p.second;
        } else {
            l = rnd.next(1LL, n - 1);
            r = rnd.next(l + 1, n);
        }

        queries.push_back({a, {l, r}});
    }

    println(n, q);
    for (auto query : queries) {
        println(query.first, query.second.first, query.second.second);
    }

    return 0;
}
