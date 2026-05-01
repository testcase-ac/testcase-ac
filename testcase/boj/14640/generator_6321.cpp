#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of photographs and time per photo
    int n = rnd.next(1, 20);
    int t = rnd.next(1, 20);
    // Decide feasibility (n=1 is always feasible)
    bool feasible = (n == 1) ? true : rnd.next(0, 1);

    vector<pair<ll,ll>> intervals;
    if (!feasible) {
        // Infeasible case: all windows are identical but too short to fit n photos
        // Choose k < n so total window length = k * t < n * t
        int k = rnd.next(1, n - 1);
        ll base = rnd.next(0LL, 20LL);
        ll windowLen = (ll)k * t;
        for (int i = 0; i < n; i++) {
            intervals.emplace_back(base, base + windowLen);
        }
    } else {
        // Feasible case: build a non-overlapping schedule s[i]
        ll maxStart = rnd.any(vector<ll>{0, 5, 10, 20});
        int maxGap = rnd.any(vector<int>{0, 1, 5, 10});
        int slackMax = rnd.any(vector<int>{0, 1, 5, 10});
        vector<ll> s(n);
        s[0] = rnd.next(0LL, maxStart);
        for (int i = 1; i < n; i++) {
            ll gap = rnd.next(0LL, (ll)maxGap);
            s[i] = s[i-1] + t + gap;
        }
        // For each photo, allow some slack before and after the ideal slot
        for (int i = 0; i < n; i++) {
            ll pre  = rnd.next(0LL, (ll)slackMax);
            ll post = rnd.next(0LL, (ll)slackMax);
            ll aLo = max(0LL, s[i] - pre);
            ll aHi = s[i];
            ll a   = rnd.next(aLo, aHi);
            ll b   = s[i] + t + post;
            intervals.emplace_back(a, b);
        }
        // Shuffle so order is not sorted by start times
        shuffle(intervals.begin(), intervals.end());
    }

    // Output
    println(n, t);
    for (auto &pr : intervals) {
        println(pr.first, pr.second);
    }
    return 0;
}
