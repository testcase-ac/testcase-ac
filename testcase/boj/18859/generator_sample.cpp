#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll MIN_A = 1;
const ll MAX_A = 1000000000LL;

vector<ll> makeArtistic(int n) {
    int leftLen = rnd.next(2, n - 1);
    int rightLen = n - leftLen + 1;
    ll leftStep = rnd.next(1, 1000000);
    ll rightStep = rnd.next(1, 1000000);
    ll maxValley = min(MAX_A - leftStep * (leftLen - 1), MAX_A - rightStep * (rightLen - 1));
    if (maxValley < MIN_A) {
        leftStep = rnd.next(1, 1000);
        rightStep = rnd.next(1, 1000);
        maxValley = min(MAX_A - leftStep * (leftLen - 1), MAX_A - rightStep * (rightLen - 1));
    }

    ll valley = rnd.next(MIN_A, maxValley);
    vector<ll> a;
    for (int i = leftLen - 1; i >= 1; --i) a.push_back(valley + leftStep * i);
    a.push_back(valley);
    for (int i = 1; i < rightLen; ++i) a.push_back(valley + rightStep * i);
    return a;
}

vector<ll> makeAlmostArtistic(int n) {
    vector<ll> a = makeArtistic(n);
    int pos = rnd.next(n);
    ll delta = rnd.next(1, 20);
    if (a[pos] + delta <= MAX_A) a[pos] += delta;
    else a[pos] -= delta;
    return a;
}

vector<ll> makeRandomSmallRange(int n) {
    ll lo = rnd.next(1, 50);
    ll hi = lo + rnd.next(0, 20);
    vector<ll> a(n);
    for (ll& x : a) x = rnd.next(lo, hi);
    return a;
}

vector<ll> makeNearBounds(int n) {
    vector<ll> choices = {1, 2, 3, 999999998LL, 999999999LL, 1000000000LL};
    vector<ll> a(n);
    for (ll& x : a) x = rnd.any(choices);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) n = rnd.next(30, 120);
    else n = rnd.next(3, 20);

    vector<ll> a;
    if (mode == 0) a = makeArtistic(n);
    else if (mode == 1) a = makeAlmostArtistic(n);
    else if (mode == 2) a = makeRandomSmallRange(n);
    else if (mode == 3) a = makeNearBounds(n);
    else if (mode == 4) {
        ll x = rnd.next(MIN_A, MAX_A);
        a.assign(n, x);
    } else {
        a = makeArtistic(n);
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);

    return 0;
}
