#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of segments
    int N = rnd.next(5, 15);
    // Coordinate range with negatives and positives
    ll Cmin = rnd.next(-20LL, -1LL);
    ll Cmax = rnd.next(1LL, 20LL);

    vector<pair<ll, ll>> segs;

    // 1) Add some touching-at-endpoint pairs (should not count as overlap)
    int numTouch = rnd.next(0, 2);
    for (int i = 0; i < numTouch; i++) {
        if ((int)segs.size() + 2 > N) break;
        // pick a touching point X in (Cmin, Cmax)
        ll X = rnd.next(Cmin + 1, Cmax - 1);
        ll L = rnd.next(Cmin, X - 1);
        ll R = rnd.next(X + 1, Cmax);
        segs.emplace_back(L, X);
        segs.emplace_back(X, R);
    }

    // 2) Add some nested segments to force overlap
    if (Cmax - Cmin >= 6) {
        int numNested = rnd.next(0, 2);
        for (int i = 0; i < numNested; i++) {
            if ((int)segs.size() >= N) break;
            // define a base large interval
            ll L0 = rnd.next(Cmin, Cmax - 5);
            ll R0 = rnd.next(L0 + 5, Cmax);
            int rem = N - (int)segs.size();
            int maxK = min(4, rem);
            // ensure we can pick at least 2 nested segments
            if (maxK < 2) break;
            int k = rnd.next(2, maxK);
            ll mid = (L0 + R0) / 2;
            for (int j = 0; j < k; j++) {
                if ((int)segs.size() >= N) break;
                ll l1 = rnd.next(L0, mid);
                ll r1 = rnd.next(mid + 1, R0);
                segs.emplace_back(l1, r1);
            }
        }
    }

    // 3) Fill remaining with random segments
    while ((int)segs.size() < N) {
        ll s = rnd.next(Cmin, Cmax - 1);
        ll e = rnd.next(s + 1, Cmax);
        segs.emplace_back(s, e);
    }

    // Shuffle for randomness
    shuffle(segs.begin(), segs.end());

    // Output
    println(N);
    for (auto &p : segs) {
        println(p.first, p.second);
    }
    return 0;
}
