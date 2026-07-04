#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Interval = pair<ll, ll>;

static vector<Interval> forbiddenFromAllowed(vector<Interval> allowed, ll k) {
    sort(allowed.begin(), allowed.end());

    vector<Interval> forbidden;
    ll pos = 0;
    for (auto [l, r] : allowed) {
        if (pos < l) forbidden.push_back({pos, l - 1});
        pos = r + 1;
    }
    if (pos < k) forbidden.push_back({pos, k - 1});

    return forbidden;
}

static ll allowedCount(const vector<Interval>& allowed) {
    ll total = 0;
    for (auto [l, r] : allowed) total += r - l + 1;
    return total;
}

static vector<Interval> makeSparseAllowed(ll k, int segments) {
    vector<Interval> allowed;
    ll pos = rnd.next(0LL, min(3LL, k - 1));

    for (int i = 0; i < segments && pos < k; ++i) {
        ll len = rnd.next(1LL, min(8LL, k - pos));
        allowed.push_back({pos, pos + len - 1});
        pos += len;
        if (i + 1 < segments && pos < k) {
            pos += rnd.next(1LL, min(7LL, k - pos));
        }
    }

    if (allowed.empty()) allowed.push_back({0, min(1LL, k - 1)});
    return allowed;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    ll n = 2;
    ll k = 2;
    vector<Interval> allowed;

    if (mode == 0) {
        k = rnd.next(2LL, 60LL);
        n = rnd.next(2LL, k);
        allowed.push_back({0, k - 1});
    } else if (mode == 1) {
        k = rnd.next(8LL, 80LL);
        int segments = rnd.next(2, 6);
        allowed = makeSparseAllowed(k, segments);
        ll total = allowedCount(allowed);
        n = rnd.next(2LL, max(2LL, total));
        if (total < n) {
            allowed.back().second = min(k - 1, allowed.back().second + (n - total));
        }
    } else if (mode == 2) {
        k = rnd.next(12LL, 120LL);
        ll leftLen = rnd.next(2LL, min(10LL, k / 3));
        ll rightLen = rnd.next(2LL, min(10LL, k / 3));
        allowed.push_back({0, leftLen - 1});
        allowed.push_back({k - rightLen, k - 1});
        if (rnd.next(0, 1)) {
            ll mid = rnd.next(leftLen + 1, k - rightLen - 2);
            allowed.push_back({mid, mid + rnd.next(0LL, min(4LL, k - rightLen - mid - 1))});
        }
        n = rnd.next(2LL, allowedCount(allowed));
    } else if (mode == 3) {
        k = rnd.next(20LL, 150LL);
        int segments = rnd.next(3, 8);
        ll pos = rnd.next(0LL, 2LL);
        for (int i = 0; i < segments && pos < k; ++i) {
            ll len = rnd.next(1LL, min(5LL, k - pos));
            allowed.push_back({pos, pos + len - 1});
            pos += len + rnd.next(1LL, min(12LL, max(1LL, k - pos)));
        }
        n = rnd.next(2LL, allowedCount(allowed));
    } else if (mode == 4) {
        k = rnd.any(vector<ll>{1000000000LL, 99999999999LL, 1000000000000LL});
        n = rnd.next(2LL, 100LL);
        ll gap = rnd.next(10LL, 1000000LL);
        allowed.push_back({0, rnd.next(0LL, 4LL)});
        allowed.push_back({gap, gap + rnd.next(1LL, 20LL)});
        allowed.push_back({k - rnd.next(20LL, 80LL), k - 1});
        if (allowedCount(allowed) < n) n = allowedCount(allowed);
    } else {
        k = rnd.next(2LL, 200LL);
        ll free = rnd.next(2LL, min(25LL, k));
        ll start = rnd.next(0LL, k - free);
        allowed.push_back({start, start + free - 1});
        n = rnd.next(2LL, free);
    }

    sort(allowed.begin(), allowed.end());
    vector<Interval> forbidden = forbiddenFromAllowed(allowed, k);
    shuffle(forbidden.begin(), forbidden.end());

    println(n, static_cast<int>(forbidden.size()), k);
    for (auto [l, r] : forbidden) {
        println(l, r);
    }

    return 0;
}
