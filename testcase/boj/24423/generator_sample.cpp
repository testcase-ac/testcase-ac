#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Point = pair<ll, ll>;

ll pickNear(ll low, ll high) {
    if (high - low <= 8) return rnd.next(low, high);
    int mode = rnd.next(0, 2);
    if (mode == 0) return low + rnd.next(0LL, 4LL);
    if (mode == 1) return high - rnd.next(0LL, 4LL);
    return rnd.next(low, high);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    ll h, w;
    vector<Point> strawberries;

    if (mode == 0) {
        h = rnd.next(3LL, 12LL);
        w = rnd.next(3LL, 12LL);
        ll top = rnd.next(1LL, h - 2);
        ll left = rnd.next(1LL, w - 2);
        int copies = rnd.next(1, 3);
        for (ll r = top; r < top + 3; ++r) {
            for (ll c = left; c < left + 3; ++c) {
                int add = rnd.next(0, copies);
                for (int k = 0; k < add; ++k) strawberries.push_back({r, c});
            }
        }
        if (strawberries.empty()) strawberries.push_back({top, left});
    } else if (mode == 1) {
        h = 3;
        w = rnd.next(3LL, rnd.next(0, 1) ? 30LL : 1000000000LL);
        ll center = pickNear(2LL, w - 1);
        int n = rnd.next(6, 30);
        for (int i = 0; i < n; ++i) {
            ll r = rnd.next(1LL, 3LL);
            ll c = max(1LL, min(w, center + rnd.next(-4LL, 4LL)));
            strawberries.push_back({r, c});
        }
    } else if (mode == 2) {
        h = rnd.next(3LL, 1000000000LL);
        w = rnd.next(3LL, 1000000000LL);
        vector<Point> anchors = {{1, 1}, {1, w}, {h, 1}, {h, w}};
        int n = rnd.next(4, 24);
        for (int i = 0; i < n; ++i) {
            Point p = rnd.any(anchors);
            ll r = max(1LL, min(h, p.first + rnd.next(-2LL, 2LL)));
            ll c = max(1LL, min(w, p.second + rnd.next(-2LL, 2LL)));
            strawberries.push_back({r, c});
        }
    } else if (mode == 3) {
        h = rnd.next(3LL, 50LL);
        w = rnd.next(3LL, 50LL);
        ll r = rnd.next(1LL, h);
        ll c = rnd.next(1LL, w);
        int duplicateCount = rnd.next(4, 20);
        for (int i = 0; i < duplicateCount; ++i) strawberries.push_back({r, c});
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) {
            strawberries.push_back({rnd.next(1LL, h), rnd.next(1LL, w)});
        }
    } else {
        h = rnd.next(3LL, 1000000LL);
        w = rnd.next(3LL, 1000000LL);
        int n = rnd.next(1, 45);
        for (int i = 0; i < n; ++i) {
            strawberries.push_back({rnd.next(1LL, h), rnd.next(1LL, w)});
        }
    }

    shuffle(strawberries.begin(), strawberries.end());
    println(h, w);
    println((int)strawberries.size());
    for (Point p : strawberries) println(p.first, p.second);

    return 0;
}
