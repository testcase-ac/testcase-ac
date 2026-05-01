#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: sometimes minimal, small, or medium
    int t = rnd.next(0, 3);
    int N;
    if (t == 0) {
        N = 1;
    } else if (t == 1) {
        N = rnd.next(2, 10);
    } else {
        N = rnd.next(10, 50);
    }

    // Decide if all points lie on y=0
    bool flat = (rnd.next(0, 3) == 0);
    int distinctYs = 1;
    if (!flat) {
        distinctYs = rnd.next(1, min(N, 5));
    }

    // Generate unique x-coordinates in [0 .. maxX]
    int maxX = max(N, 10) * 5;
    vector<int> xs(maxX + 1);
    iota(xs.begin(), xs.end(), 0);
    shuffle(xs.begin(), xs.end());
    xs.resize(N);

    // Generate y-coordinate values
    vector<int> ys_vals;
    if (flat) {
        ys_vals = {0};
    } else {
        int maxY = max(distinctYs, 10) * 5;
        vector<int> tmp(maxY + 1);
        iota(tmp.begin(), tmp.end(), 0);
        shuffle(tmp.begin(), tmp.end());
        tmp.resize(distinctYs);
        ys_vals = tmp;
    }

    // Weight mode: 0 = mixed positives/negatives, 1 = exactly one negative
    int weightMode = (N > 1 ? rnd.next(0, 1) : 0);
    int negIdx = -1;
    if (weightMode == 1) {
        negIdx = rnd.next(0, N - 1);
    }

    // Generate weights, ensure at least one positive
    vector<long long> ws(N);
    int positiveCount = 0;
    for (int i = 0; i < N; i++) {
        if (weightMode == 1 && i == negIdx) {
            ws[i] = -rnd.next(1, 1000);
        } else {
            if (weightMode == 0 && rnd.next(0, 4) == 0) {
                ws[i] = -rnd.next(1, 1000);
            } else {
                ws[i] = rnd.next(1, 1000);
                positiveCount++;
            }
        }
    }
    if (positiveCount == 0) {
        int idx = rnd.next(0, N - 1);
        ws[idx] = rnd.next(1, 1000);
    }

    // Build and shuffle points
    vector<tuple<int,int,long long>> pts;
    pts.reserve(N);
    for (int i = 0; i < N; i++) {
        int x = xs[i];
        int y = flat ? 0 : ys_vals[i % distinctYs];
        pts.emplace_back(x, y, ws[i]);
    }
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        int x, y; long long w;
        tie(x, y, w) = p;
        println(x, y, w);
    }

    return 0;
}
