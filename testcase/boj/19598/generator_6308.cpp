#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of meetings
    int N = rnd.next(1, 12);
    vector<pair<ll,ll>> intervals;
    // Generation mode: 0=sparse non-overlap, 1=clustered overlap,
    // 2=fully random, 3=heavy overlap
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Sparse: non-overlapping intervals in increasing time
        ll current = rnd.next(0, 5);
        for (int i = 0; i < N; i++) {
            ll start = current + rnd.next(0, 3);
            ll dur   = rnd.next(1, 5);
            ll end   = start + dur;
            intervals.emplace_back(start, end);
            current = end;
        }
    } else if (mode == 1) {
        // Clustered: several clusters where intervals may overlap
        int K = rnd.next(1, min(3, N));
        vector<ll> base(K);
        for (int i = 0; i < K; i++)
            base[i] = rnd.next(0, 10);
        for (int i = 0; i < N; i++) {
            int c = rnd.next(0, K - 1);
            // offset in [-2,2]
            ll off = rnd.next(0, 4) - 2;
            ll start = base[c] + off;
            if (start < 0) start = 0;
            ll dur = rnd.next(1, 5);
            ll end = start + dur;
            intervals.emplace_back(start, end);
        }
    } else if (mode == 2) {
        // Fully random intervals
        for (int i = 0; i < N; i++) {
            ll start = rnd.next(0, 20);
            ll dur   = rnd.next(1, 10);
            ll end   = start + dur;
            intervals.emplace_back(start, end);
        }
    } else {
        // Heavy overlap: small window, large durations
        for (int i = 0; i < N; i++) {
            ll start = rnd.next(0, 5);
            ll dur   = rnd.next(5, 12);
            ll end   = start + dur;
            intervals.emplace_back(start, end);
        }
    }
    // Shuffle order to mix start times
    shuffle(intervals.begin(), intervals.end());
    // Occasionally force an exact end==start boundary between two intervals
    if (N >= 2 && rnd.next(0, 3) == 0) {
        // pick a target j with start>=1 so we can shift safely
        vector<int> good;
        for (int i = 0; i < N; i++)
            if (intervals[i].first >= 1)
                good.push_back(i);
        if (!good.empty()) {
            int j = rnd.any(good);
            // pick an i != j
            int i;
            do { i = rnd.next(0, N - 1); } while (i == j);
            intervals[i].second = intervals[j].first;
            // ensure start < end
            if (intervals[i].first >= intervals[i].second) {
                intervals[i].first = intervals[i].second - 1;
                if (intervals[i].first < 0)
                    intervals[i].first = 0;
            }
        }
    }
    // Output
    println(N);
    for (auto &p : intervals)
        println(p.first, p.second);
    return 0;
}
