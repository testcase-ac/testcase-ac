#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using ll = long long;
using Banana = tuple<ll, ll, int>;

ll normalizeColumn(ll column, ll m) {
    if (m == 1) return 1;

    ll period = 2 * (m - 1);
    ll p = (column - 1) % period;
    if (p < 0) p += period;
    return p < m ? p + 1 : period - p + 1;
}

ll startColumnForArrival(ll target, ll row, int dir, ll m) {
    return normalizeColumn(target - dir * (row - 1), m);
}

void addBanana(vector<Banana>& bananas, set<pair<ll, ll>>& used, ll row, ll col, int dir) {
    if (!used.insert({row, col}).second) return;
    bananas.emplace_back(row, col, dir);
}

void addBananaForArrival(vector<Banana>& bananas, set<pair<ll, ll>>& used,
                         ll n, ll m, ll target, int rowSpan) {
    for (int attempt = 0; attempt < 40; ++attempt) {
        ll row = rnd.next(2LL, min(n, static_cast<ll>(rowSpan)));
        int dir = rnd.next(0, 1) == 0 ? -1 : 1;
        ll col = startColumnForArrival(target, row, dir, m);
        size_t before = bananas.size();
        addBanana(bananas, used, row, col, dir);
        if (bananas.size() != before) return;
    }
}

void fillRandom(vector<Banana>& bananas, set<pair<ll, ll>>& used, ll n, ll m, int targetSize) {
    while (static_cast<int>(bananas.size()) < targetSize) {
        addBanana(bananas, used, rnd.next(2LL, n), rnd.next(1LL, m),
                  rnd.next(0, 1) == 0 ? -1 : 1);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    ll n;
    ll m;
    vector<Banana> bananas;
    set<pair<ll, ll>> used;

    if (mode == 0) {
        n = rnd.next(2LL, 8LL);
        m = rnd.next(1LL, 8LL);
        int x = rnd.next(1, static_cast<int>(min(12LL, (n - 1) * m)));
        fillRandom(bananas, used, n, m, x);
    } else if (mode == 1) {
        n = rnd.next(4LL, 20LL);
        m = rnd.next(2LL, 10LL);
        ll target = rnd.next(1LL, m);
        int x = rnd.next(4, min(18, static_cast<int>((n - 1) * m)));
        int targeted = rnd.next(2, min(x, 8));
        for (int i = 0; i < targeted; ++i) {
            addBananaForArrival(bananas, used, n, m, target, 20);
        }
        fillRandom(bananas, used, n, m, x);
    } else if (mode == 2) {
        n = rnd.next(8LL, 40LL);
        m = rnd.next(2LL, 12LL);
        int groups = rnd.next(2, static_cast<int>(min(5LL, m)));
        for (int g = 0; g < groups; ++g) {
            ll target = rnd.next(1LL, m);
            int count = rnd.next(2, 5);
            for (int i = 0; i < count; ++i) addBananaForArrival(bananas, used, n, m, target, 40);
        }
    } else if (mode == 3) {
        n = rnd.next(2LL, 1000000000LL);
        m = rnd.next(1LL, 1000000000LL);
        int x = rnd.next(1, 12);
        fillRandom(bananas, used, n, m, x);
    } else if (mode == 4) {
        n = 1000000000LL - rnd.next(0LL, 1000LL);
        m = 1000000000LL - rnd.next(0LL, 1000LL);
        ll target = rnd.next(m - 20, m);
        int x = rnd.next(6, 16);
        int targeted = rnd.next(3, min(x, 8));
        for (int i = 0; i < targeted; ++i) {
            ll row = rnd.next(max(2LL, n - 2000), n);
            int dir = rnd.next(0, 1) == 0 ? -1 : 1;
            addBanana(bananas, used, row, startColumnForArrival(target, row, dir, m), dir);
        }
        fillRandom(bananas, used, n, m, x);
    } else {
        n = rnd.next(10LL, 80LL);
        m = rnd.next(1LL, 4LL);
        int x = rnd.next(8, min(30, static_cast<int>((n - 1) * m)));
        fillRandom(bananas, used, n, m, x);
    }

    shuffle(bananas.begin(), bananas.end());

    println(n, m, static_cast<int>(bananas.size()));
    for (auto [row, col, dir] : bananas) println(row, col, dir);

    return 0;
}
