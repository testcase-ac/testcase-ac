#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

static constexpr ll kMaxValue = 1000000000LL;

static pair<ll, ll> boundedEnemy(ll m, int mode) {
    if (mode == 0) {
        ll t = rnd.next(1LL, min(12LL, m));
        ll h = rnd.next(t, min(kMaxValue, max(t, m + 8)));
        return {t, h};
    }
    if (mode == 1) {
        ll t = rnd.next(m + 1, min(kMaxValue, m + 20));
        ll h = rnd.next(1LL, min(kMaxValue, max(1LL, m - 1)));
        return {t, h};
    }
    if (mode == 2) {
        ll t = rnd.next(1LL, min(kMaxValue, m + 8));
        ll h = rnd.next(1LL, kMaxValue);
        return {t, h};
    }

    ll t = rnd.next(1LL, min(kMaxValue, m + 20));
    ll h = rnd.next(1LL, min(kMaxValue, m + 20));
    return {t, h};
}

static vector<pair<ll, ll>> makeEnemies(int n, ll m, int mode) {
    vector<pair<ll, ll>> enemies;
    enemies.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            enemies.push_back(boundedEnemy(m, i % 4));
        }
    } else if (mode == 1) {
        ll boundary = rnd.next(1LL, min(kMaxValue, m + 2));
        enemies.push_back({boundary, rnd.next(1LL, kMaxValue)});
        for (int i = 1; i < n; ++i) {
            enemies.push_back(boundedEnemy(m, rnd.next(0, 3)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            ll t = rnd.next(max(1LL, m - 3), min(kMaxValue, m + 6));
            ll h = rnd.next(1LL, min(kMaxValue, m + 6));
            enemies.push_back({t, h});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            ll t = rnd.next(1LL, min(kMaxValue, m + 15));
            ll h = (i % 3 == 0) ? rnd.next(m, kMaxValue) : rnd.next(1LL, min(kMaxValue, m + 15));
            enemies.push_back({t, h});
        }
    }

    shuffle(enemies.begin(), enemies.end());
    return enemies;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(6, 12);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = tc % 4;
        int n = rnd.next(1, 9);
        ll m;
        if (tc == 0) {
            m = 1;
        } else if (mode == 3) {
            m = rnd.next(1LL, 1000000000LL);
            n = rnd.next(1, 5);
        } else {
            m = rnd.next(2LL, 20LL);
        }

        vector<pair<ll, ll>> enemies = makeEnemies(n, m, mode);

        println(n, m);
        for (const auto& enemy : enemies) {
            println(enemy.first, enemy.second);
        }
    }

    return 0;
}
