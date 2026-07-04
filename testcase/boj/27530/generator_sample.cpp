#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

static ll coord(ll limit, int flavor) {
    if (limit == 1) return 1;
    if (flavor == 0) return 1;
    if (flavor == 1) return limit;
    if (flavor == 2) return (limit + 1) / 2;
    return rnd.next(1LL, limit);
}

static pair<ll, ll> point(ll n, ll m, int mode) {
    if (mode == 1 && rnd.next(100) < 70) {
        return {coord(n, rnd.next(3)), coord(m, rnd.next(3))};
    }
    if (mode == 2 && rnd.next(100) < 60) {
        ll y = coord(n, rnd.next(2));
        return {y, rnd.next(1LL, m)};
    }
    if (mode == 3 && rnd.next(100) < 60) {
        ll x = coord(m, rnd.next(2));
        return {rnd.next(1LL, n), x};
    }
    return {rnd.next(1LL, n), rnd.next(1LL, m)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    ll n, m;
    if (mode == 0) {
        n = rnd.next(1LL, 8LL);
        m = rnd.next(1LL, 8LL);
    } else if (mode == 1) {
        n = rnd.any(vector<ll>{1LL, 2LL, 3LL, 1000000000LL});
        m = rnd.any(vector<ll>{1LL, 2LL, 5LL, 1000000000LL});
    } else if (mode == 2) {
        n = rnd.next(1LL, 3LL);
        m = rnd.next(8LL, 30LL);
    } else if (mode == 3) {
        n = rnd.next(8LL, 30LL);
        m = rnd.next(1LL, 3LL);
    } else {
        n = rnd.next(20LL, 100LL);
        m = rnd.next(20LL, 100LL);
    }

    int k = rnd.next(1, mode == 4 ? 18 : 10);
    int q = rnd.next(1, mode == 4 ? 18 : 10);

    vector<pair<ll, ll>> people;
    vector<pair<ll, ll>> ufos;

    for (int i = 0; i < k; ++i) {
        if (!people.empty() && rnd.next(100) < 25) {
            people.push_back(rnd.any(people));
        } else {
            people.push_back(point(n, m, mode));
        }
    }

    for (int i = 0; i < q; ++i) {
        if (!ufos.empty() && rnd.next(100) < 25) {
            ufos.push_back(rnd.any(ufos));
        } else if (!people.empty() && rnd.next(100) < 25) {
            ufos.push_back(rnd.any(people));
        } else {
            ufos.push_back(point(n, m, mode));
        }
    }

    println(n, m, k, q);
    for (auto [y, x] : people) {
        println(y, x);
    }
    for (auto [y, x] : ufos) {
        ll t;
        int timeMode = rnd.next(4);
        if (timeMode == 0) {
            t = 1;
        } else if (timeMode == 1) {
            t = rnd.next(1LL, 5LL);
        } else if (timeMode == 2) {
            t = max(n, m);
        } else {
            t = 1000000000LL;
        }
        println(y, x, t);
    }

    return 0;
}
