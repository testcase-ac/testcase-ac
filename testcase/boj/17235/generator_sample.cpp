#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

static const ll LIMIT = 1000000000LL;

static ll clampCoord(ll value) {
    return max(-LIMIT, min(LIMIT, value));
}

static pair<ll, ll> fromUV(ll u, ll v) {
    ll x = (u + v) / 2;
    ll y = (u - v) / 2;
    return {clampCoord(x), clampCoord(y)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<ll, ll>> points;

    if (mode == 0) {
        int n = rnd.next(2, 18);
        int radius = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(-radius, radius), rnd.next(-radius, radius)});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        ll u = rnd.next(-30, 30) * 2LL;
        for (int i = 0; i < n; ++i) {
            ll v = rnd.next(-30, 30) * 2LL;
            points.push_back(fromUV(u, v));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 20);
        ll v = rnd.next(-30, 30) * 2LL;
        for (int i = 0; i < n; ++i) {
            ll u = rnd.next(-30, 30) * 2LL;
            points.push_back(fromUV(u, v));
        }
    } else if (mode == 3) {
        int radius = rnd.next(1, 30);
        points = {{radius, 0}, {-radius, 0}, {0, radius}, {0, -radius}};
        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(-radius, radius);
            int span = radius - abs(x);
            points.push_back({x, rnd.next(-span, span)});
        }
    } else if (mode == 4) {
        ll base = rnd.any(vector<ll>{-LIMIT, LIMIT});
        int n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            ll dx = rnd.next(0, 20);
            ll dy = rnd.next(0, 20);
            points.push_back({clampCoord(base + (base < 0 ? dx : -dx)),
                              clampCoord(base + (base < 0 ? dy : -dy))});
        }
    } else {
        int n = rnd.next(2, 24);
        ll minU = rnd.next(-40, 0) * 2LL;
        ll maxU = rnd.next(0, 40) * 2LL;
        ll minV = rnd.next(-40, 0) * 2LL;
        ll maxV = rnd.next(0, 40) * 2LL;
        points.push_back(fromUV(minU, rnd.next((int)minV, (int)maxV) / 2 * 2LL));
        points.push_back(fromUV(maxU, rnd.next((int)minV, (int)maxV) / 2 * 2LL));
        points.push_back(fromUV(rnd.next((int)minU, (int)maxU) / 2 * 2LL, minV));
        points.push_back(fromUV(rnd.next((int)minU, (int)maxU) / 2 * 2LL, maxV));
        while ((int)points.size() < n) {
            ll u = rnd.next((int)minU, (int)maxU) / 2 * 2LL;
            ll v = rnd.next((int)minV, (int)maxV) / 2 * 2LL;
            points.push_back(fromUV(u, v));
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
