#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int prefixCost(vector<int> a) {
    sort(a.begin(), a.end());
    int sum = 0;
    int cost = 0;
    for (int x : a) {
        sum += x;
        cost += sum;
    }
    return cost;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    vector<int> a, p;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 6);
        a.resize(n);
        p.resize(n);
        int lo = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, lo + 20);
            p[i] = rnd.next(1, 50);
        }
        k = rnd.next(1, lo - 1);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        a.resize(n);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 8);
            p[i] = rnd.next(1, 100);
        }
        k = rnd.next(prefixCost(a), 100000);
    } else if (mode == 2) {
        n = rnd.next(5, 12);
        a.resize(n);
        p.resize(n);
        int base = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a[i] = base + rnd.next(0, 2);
            p[i] = rnd.next(1, 3) == 1 ? rnd.next(200, 1000) : rnd.next(1, 30);
        }
        vector<int> sortedA = a;
        sort(sortedA.begin(), sortedA.end());
        int take = rnd.next(1, n);
        sortedA.resize(take);
        k = max(1, prefixCost(sortedA) + rnd.next(-base, base));
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        a.resize(n);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 3 == 0) ? rnd.next(200, 2000) : rnd.next(1, 20);
            p[i] = (i % 3 == 0) ? rnd.next(500, 5000) : rnd.next(1, 100);
        }
        k = rnd.next(1, min(100000, prefixCost(a)));
    } else if (mode == 4) {
        n = rnd.next(13, 20);
        a.resize(n);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 30);
            p[i] = rnd.next(1, 200);
        }
        k = rnd.next(1, min(100000, prefixCost(a)));
    } else if (mode == 5) {
        n = rnd.next(2, 8);
        a.resize(n);
        p.resize(n);
        int value = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = value;
            p[i] = rnd.next(1, 100000);
        }
        long long maxTake = rnd.next(1, n);
        long long exact = value * maxTake * (maxTake + 1) / 2;
        k = (int)min(100000LL, max(1LL, exact + rnd.next(-value / 2, value / 2)));
    } else {
        n = rnd.next(1, 20);
        a.resize(n);
        p.resize(n);
        int aHi = rnd.next(1, 100000);
        int pHi = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, aHi);
            p[i] = rnd.next(1, pHi);
        }
        k = rnd.next(1, 100000);
    }

    shuffle(a.begin(), a.end());
    shuffle(p.begin(), p.end());

    println(n, k);
    println(a);
    println(p);
    return 0;
}
