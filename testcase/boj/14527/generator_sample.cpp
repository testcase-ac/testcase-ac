#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_X = 1000000000LL;
    const ll MAX_Y = 1000000000LL;

    vector<pair<ll, ll>> groups;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        ll x = 2LL * rnd.next(1, 20);
        ll y = rnd.next(1LL, 50LL);
        groups.push_back({x, y});
    } else {
        int n = rnd.next(2, mode == 5 ? 30 : 12);
        vector<ll> ys;

        if (mode == 1) {
            ll base = rnd.next(1LL, 20LL);
            for (int i = 0; i < n; ++i) ys.push_back(base + rnd.next(0, 3));
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) ys.push_back(1LL + i * rnd.next(1, 7));
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) ys.push_back(rnd.next(1LL, 1000LL));
        } else if (mode == 4) {
            ys = {1LL, MAX_Y};
            while ((int)ys.size() < n) ys.push_back(rnd.next(1LL, MAX_Y));
        } else {
            for (int i = 0; i < n; ++i) ys.push_back(rnd.next(1LL, 100000LL));
        }

        for (int i = 0; i < n; ++i) {
            ll x;
            if (mode == 5 && rnd.next(0, 4) == 0) {
                x = rnd.next(1000000LL, 20000000LL);
            } else {
                x = rnd.next(1LL, 20LL);
            }
            groups.push_back({x, ys[i]});
        }
    }

    ll total = 0;
    for (auto [x, y] : groups) {
        (void)y;
        total += x;
    }

    if (total % 2 == 1) {
        if (groups[0].first < MAX_X) {
            ++groups[0].first;
        } else {
            --groups[0].first;
        }
    }

    shuffle(groups.begin(), groups.end());

    println((int)groups.size());
    for (auto [x, y] : groups) {
        println(x, y);
    }

    return 0;
}
