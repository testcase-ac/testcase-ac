#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

long long clampValue(long long x) {
    return max(-1000000000LL, min(1000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(8, 30);
        m = rnd.next(8, 30);
    } else {
        n = rnd.next(20, 80);
        m = rnd.next(20, 80);
    }

    vector<long long> pool;
    if (mode == 0) {
        pool.push_back(rnd.any(vector<long long>{-1000000000LL, -1LL, 0LL, 1LL, 1000000000LL}));
    } else if (mode == 3) {
        long long base = rnd.next(-20, 20);
        for (int i = -4; i <= 4; ++i) pool.push_back(base + i);
    } else if (mode == 4) {
        pool = {-1000000000LL, -999999999LL, -1LL, 0LL, 1LL, 999999999LL, 1000000000LL};
    } else {
        int distinct = rnd.next(2, min(n, 12));
        long long lo = rnd.next(-50, 20);
        long long hi = rnd.next(lo + distinct - 1, lo + 80);
        set<long long> values;
        while ((int)values.size() < distinct) values.insert(rnd.next(lo, hi));
        pool.assign(values.begin(), values.end());
    }

    vector<long long> a;
    for (int i = 0; i < n; ++i) {
        long long x = rnd.any(pool);
        if (mode == 5 && rnd.next(0, 3) == 0) x = rnd.next(-1000, 1000);
        a.push_back(x);
    }

    if (mode == 0) a[0] = pool[0];
    if (mode == 4 && n >= 7) {
        for (int i = 0; i < 7; ++i) a[i] = pool[i];
    }

    vector<long long> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    vector<long long> queries;
    for (int i = 0; i < m; ++i) {
        int kind = rnd.next(0, 5);
        long long q;
        if (kind <= 2) {
            q = rnd.any(sorted);
        } else if (kind == 3) {
            q = clampValue(rnd.any(sorted) + rnd.any(vector<long long>{-2LL, -1LL, 1LL, 2LL}));
        } else if (kind == 4) {
            q = rnd.next(-60, 60);
        } else {
            q = rnd.any(vector<long long>{-1000000000LL, -999999999LL, 0LL, 999999999LL, 1000000000LL});
        }
        queries.push_back(q);
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        sort(a.begin(), a.end());
    } else if (order == 1) {
        sort(a.rbegin(), a.rend());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n, m);
    for (long long x : a) println(x);
    for (long long q : queries) println(q);

    return 0;
}
