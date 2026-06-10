#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_MONEY = 1000000000000000000LL;

ll pickNear(ll center, ll radius) {
    ll lo = max(1LL, center - radius);
    ll hi = min(MAX_MONEY, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 8);
    vector<pair<ll, ll>> citizens;
    vector<pair<ll, int>> shops;

    if (mode == 0) {
        ll price = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            ll l = rnd.next(1LL, price);
            ll r = rnd.next(price, price + 20);
            citizens.push_back({l, r});
        }
        shops.push_back({price, rnd.next(1, 1000)});
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        m = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            ll l = rnd.next(1LL, 80LL);
            ll r = l + rnd.next(0LL, 8LL);
            citizens.push_back({l, r});
        }
        for (int j = 0; j < m; ++j) {
            ll p = rnd.next(1LL, 100LL);
            shops.push_back({p, rnd.next(1, 3)});
        }
    } else if (mode == 2) {
        n = rnd.next(5, 12);
        m = rnd.next(3, 8);
        ll base = rnd.next(10LL, 100LL);
        for (int i = 0; i < n; ++i) {
            ll l = base + rnd.next(-5LL, 5LL);
            ll r = l + rnd.next(0LL, 12LL);
            citizens.push_back({max(1LL, l), min(MAX_MONEY, r)});
        }
        for (int j = 0; j < m; ++j) {
            shops.push_back({pickNear(base + 4, 10), rnd.next(1, 4)});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 8);
        vector<ll> anchors = {1LL, 2LL, MAX_MONEY - 2, MAX_MONEY - 1, MAX_MONEY};
        for (int i = 0; i < n; ++i) {
            ll a = rnd.any(anchors);
            ll b = pickNear(a, 2);
            if (a > b) swap(a, b);
            citizens.push_back({a, b});
        }
        for (int j = 0; j < m; ++j) {
            shops.push_back({rnd.any(anchors), rnd.next(1, 1000)});
        }
    } else if (mode == 4) {
        n = rnd.next(6, 12);
        m = rnd.next(3, 7);
        for (int i = 0; i < n; ++i) {
            ll l = 10LL * rnd.next(1, 9);
            citizens.push_back({l, l});
        }
        for (int j = 0; j < m; ++j) {
            shops.push_back({10LL * rnd.next(1, 9), rnd.next(1, 2)});
        }
    } else {
        n = rnd.next(1, 10);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            ll l = rnd.next(1LL, 1000LL);
            ll r = rnd.next(l, 1000LL);
            citizens.push_back({l, r});
        }
        for (int j = 0; j < m; ++j) {
            shops.push_back({rnd.next(1LL, 1000LL), rnd.next(1, 1000)});
        }
    }

    shuffle(citizens.begin(), citizens.end());
    shuffle(shops.begin(), shops.end());

    println(n, m);
    for (auto [l, r] : citizens) println(l, r);
    for (auto [p, x] : shops) println(p, x);

    return 0;
}
