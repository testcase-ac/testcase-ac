#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

struct Frog {
    ll a;
    ll b;
    ll c;
};

static ll rand_ll(ll lo, ll hi) {
    return rnd.next(lo, hi);
}

static Frog reachable_from(ll x, ll y, ll c) {
    ll dx = rand_ll(-c, c);
    ll rem = c - llabs(dx);
    ll dy = rand_ll(-rem, rem);
    if (((c - llabs(dx) - llabs(dy)) & 1LL) != 0) {
        if (dy < rem) {
            ++dy;
        } else {
            --dy;
        }
    }
    return {x + dx, y + dy, c};
}

static Frog random_frog(ll coord_limit, ll c_limit) {
    return {
        rand_ll(-coord_limit, coord_limit),
        rand_ll(-coord_limit, coord_limit),
        rand_ll(0, c_limit),
    };
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    vector<Frog> frogs;

    if (mode == 0) {
        ll x = rand_ll(-20, 20);
        ll y = rand_ll(-20, 20);
        for (int i = 0; i < n; ++i) {
            frogs.push_back(reachable_from(x, y, rand_ll(0, 40)));
        }
    } else if (mode == 1) {
        ll x = rand_ll(-30, 30);
        ll y = rand_ll(-30, 30);
        frogs.push_back(reachable_from(x, y, rand_ll(1, 30)));
        Frog bad = reachable_from(x, y, rand_ll(1, 30));
        if (bad.c < 2000000000LL) {
            ++bad.c;
        } else {
            --bad.c;
        }
        frogs.push_back(bad);
        while ((int)frogs.size() < n) {
            frogs.push_back(random_frog(50, 60));
        }
    } else if (mode == 2) {
        frogs.push_back({-1000000000LL, -1000000000LL, 0});
        frogs.push_back({1000000000LL, 1000000000LL, 0});
        while ((int)frogs.size() < n) {
            frogs.push_back(random_frog(100, 100));
        }
    } else if (mode == 3) {
        vector<pair<ll, ll>> starts = {
            {-1000000000LL, -1000000000LL},
            {-1000000000LL, 1000000000LL},
            {1000000000LL, -1000000000LL},
            {1000000000LL, 1000000000LL},
            {0, 0},
        };
        auto [x, y] = rnd.any(starts);
        n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            frogs.push_back(reachable_from(x, y, rand_ll(0, 2000000000LL)));
            frogs.back().a = max(-1000000000LL, min(1000000000LL, frogs.back().a));
            frogs.back().b = max(-1000000000LL, min(1000000000LL, frogs.back().b));
        }
    } else {
        n = 1;
        frogs.push_back(random_frog(1000000000LL, 2000000000LL));
    }

    shuffle(frogs.begin(), frogs.end());

    println((int)frogs.size());
    for (const Frog& frog : frogs) {
        println(frog.a, frog.b, frog.c);
    }

    return 0;
}
