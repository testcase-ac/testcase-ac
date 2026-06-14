#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

vector<ll> randomArray(int n, ll lo, ll hi) {
    vector<ll> a(n);
    for (ll& x : a) x = rnd.next(lo, hi);
    return a;
}

vector<ll> edgeHeavyArray(int n, bool heavyFront) {
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        bool edge = heavyFront ? i < n / 3 : i >= n - n / 3;
        a[i] = edge ? rnd.next(500000000LL, 1000000000LL) : rnd.next(1LL, 1000LL);
    }
    return a;
}

vector<ll> middleLightArray(int n) {
    vector<ll> a(n, rnd.next(1000000LL, 1000000000LL));
    int len = rnd.next(1, n);
    int start = rnd.next(0, n - len);
    for (int i = start; i < start + len; ++i) a[i] = rnd.next(1LL, 1000LL);
    return a;
}

vector<ll> alternatingArray(int n, ll low, ll high) {
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) a[i] = rnd.next(1LL, low);
        else a[i] = rnd.next(high, 1000000000LL);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) n = rnd.next(1, 4);
    else if (mode == 6) n = rnd.next(30, 80);
    else n = rnd.next(5, 25);

    int kMode = rnd.next(0, 5);
    int k;
    if (kMode == 0) k = 0;
    else if (kMode == 1) k = n;
    else if (kMode == 2) k = 1;
    else if (kMode == 3) k = max(0, n - 1);
    else k = rnd.next(0, n);

    vector<ll> a, b;
    if (mode == 0) {
        a = randomArray(n, 1, 20);
        b = randomArray(n, 1, 20);
    } else if (mode == 1) {
        ll value = rnd.next(1LL, 1000000000LL);
        a.assign(n, value);
        b.assign(n, value);
    } else if (mode == 2) {
        a = edgeHeavyArray(n, true);
        b = edgeHeavyArray(n, false);
    } else if (mode == 3) {
        a = middleLightArray(n);
        b = middleLightArray(n);
    } else if (mode == 4) {
        a = alternatingArray(n, 1000, 500000000LL);
        b = alternatingArray(n, 1000, 500000000LL);
        reverse(b.begin(), b.end());
    } else if (mode == 5) {
        a = randomArray(n, 1, 1000000);
        b = a;
        for (ll& x : b) x = max(1LL, min(1000000000LL, x + rnd.next(-10LL, 10LL)));
    } else {
        a = randomArray(n, 1, 1000000000LL);
        b = randomArray(n, 1, 1000000000LL);
    }

    println(n, k);
    println(a);
    println(b);
    return 0;
}
