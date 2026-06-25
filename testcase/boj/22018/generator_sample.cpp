#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

struct Picture {
    ll x;
    ll v;
};

ll randomValue(int band) {
    if (band == 0) return rnd.next(1, 3);
    if (band == 1) return rnd.next(4, 20);
    if (band == 2) return rnd.next(21, 1000);
    return rnd.next(900000000, 1000000000);
}

void addUnique(vector<Picture>& pictures, set<ll>& used, ll x, ll v) {
    while (used.count(x) || x > 1000000000) {
        x = (x % 1000000000) + 1;
    }
    used.insert(x);
    pictures.push_back({x, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int m = rnd.next(1, n);
    ll d = rnd.next(1, 40);
    vector<Picture> pictures;
    set<ll> used;

    if (mode == 0) {
        m = 1;
        d = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            addUnique(pictures, used, rnd.next(1, 1000000), randomValue(rnd.next(0, 3)));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        m = n;
        d = rnd.next(1, 15);
        ll x = rnd.next(1, 10);
        bool forceFeasible = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            ll step = forceFeasible ? rnd.next((int)d, (int)d + 6) : rnd.next(1, max(1, (int)d - 1));
            if (i > 0) x += step;
            addUnique(pictures, used, x, randomValue(i % 3));
        }
    } else if (mode == 2) {
        n = rnd.next(8, 28);
        m = rnd.next(2, min(n, 8));
        d = rnd.next(6, 40);
        ll base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            ll x = base + rnd.next(0, (int)d - 1) + (i / 6) * (d + rnd.next(1, 4));
            addUnique(pictures, used, x, randomValue(i % 2));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 26);
        m = rnd.next(2, min(n, 10));
        d = rnd.next(2, 30);
        ll x = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (i > 0) x += rnd.next((int)d, (int)d + 10);
            int band = (i % 3 == 0) ? 0 : rnd.next(1, 2);
            addUnique(pictures, used, x, randomValue(band));
        }
    } else if (mode == 4) {
        n = rnd.next(10, 35);
        m = rnd.next(3, min(n, 12));
        d = rnd.next(3, 25);
        ll x = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            if (i > 0) x += rnd.next(1, (int)d + 5);
            int band = (i % 4 == 0) ? 3 : rnd.next(0, 2);
            addUnique(pictures, used, x, randomValue(band));
        }
    } else {
        n = rnd.next(2, 20);
        m = rnd.next(1, n);
        d = rnd.next(999999900, 1000000000);
        addUnique(pictures, used, 1, randomValue(3));
        addUnique(pictures, used, 1000000000, randomValue(3));
        for (int i = 2; i < n; ++i) {
            addUnique(pictures, used, rnd.next(2, 999999999), randomValue(rnd.next(0, 3)));
        }
    }

    shuffle(pictures.begin(), pictures.end());

    println((int)pictures.size(), m, d);
    for (const Picture& picture : pictures) {
        println(picture.x, picture.v);
    }

    return 0;
}
