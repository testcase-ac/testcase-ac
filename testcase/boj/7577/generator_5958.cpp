#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose K between 3 and 40
    int K = rnd.next(3, 40);

    // Choose bit density p: biased to some edge and middle cases
    double p;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // sparse
        p = rnd.next() * 0.2;           // [0,0.2)
    } else if (mode == 1) {
        // dense
        p = 0.8 + rnd.next() * 0.2;     // [0.8,1.0)
    } else {
        // uniform medium
        p = 0.2 + rnd.next() * 0.6;     // [0.2,0.8)
    }

    // Generate the hidden string
    vector<int> a(K);
    for (int i = 0; i < K; i++) {
        a[i] = (rnd.next() < p ? 1 : 0);
    }
    // Sometimes force an all-zero or all-one edge-case
    if (rnd.next(0, 9) == 0) {
        if (rnd.next(0, 1)) {
            fill(a.begin(), a.end(), 0);
        } else {
            fill(a.begin(), a.end(), 1);
        }
    }

    // Build prefix sums
    vector<int> pref(K+1, 0);
    for (int i = 0; i < K; i++) {
        pref[i+1] = pref[i] + a[i];
    }

    // Total possible intervals
    int maxIntervals = K * (K + 1) / 2;
    // Choose N: few, random, or maximal
    int N;
    int rmode = rnd.next(0, 2);
    if (rmode == 0) {
        N = 2;
    } else if (rmode == 1) {
        N = rnd.next(2, maxIntervals);
    } else {
        N = maxIntervals;
    }

    // Generate N distinct intervals with varied sizes
    set<pair<int,int>> used;
    vector<pair<int,int>> qs;
    qs.reserve(N);
    int attempts = 0;
    while ((int)qs.size() < N && attempts < N * 10) {
        attempts++;
        int sz;
        int t = rnd.next(1, 100);
        if (t <= 20) {
            sz = 1;
        } else if (t <= 50) {
            sz = rnd.next(2, min(3, K));
        } else if (t <= 80 && K >= 4) {
            sz = rnd.next(4, max(4, K/2));
        } else {
            sz = rnd.next(1, K);
        }
        if (sz > K) sz = K;
        int x = rnd.next(1, K - sz + 1);
        int y = x + sz - 1;
        auto pr = make_pair(x, y);
        if (!used.count(pr)) {
            used.insert(pr);
            qs.push_back(pr);
        }
    }
    // If not enough, fill up with random intervals
    while ((int)qs.size() < N) {
        int x = rnd.next(1, K);
        int y = rnd.next(x, K);
        auto pr = make_pair(x, y);
        if (!used.count(pr)) {
            used.insert(pr);
            qs.push_back(pr);
        }
    }

    // Shuffle to randomize order
    shuffle(qs.begin(), qs.end());

    // Output
    println(K, N);
    for (auto &pr : qs) {
        int x = pr.first, y = pr.second;
        int r = pref[y] - pref[x-1];
        println(x, y, r);
    }

    return 0;
}
