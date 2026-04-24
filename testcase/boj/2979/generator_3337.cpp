#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for rate caps: small, medium, or large
    int style = rnd.next(0, 2);
    int cap;
    if (style == 0) cap = rnd.next(5, 20);
    else if (style == 1) cap = rnd.next(20, 50);
    else cap = rnd.next(50, 100);

    // Generate C <= B <= A
    int C = rnd.next(1, cap);
    int B = rnd.next(C, cap);
    int A = rnd.next(B, cap);
    // Occasionally force some equal rates
    if (rnd.next() < 0.3) {
        if (rnd.next(0, 1) == 0) B = C;
        else A = B;
    }

    // Total time horizon small for hand‐checking
    int maxTime = rnd.next(5, 20);

    // Decide one of three interval‐generation modes
    vector<pair<int,int>> intervals;
    double dp = rnd.next();

    // Mode 1: disjoint intervals (only if enough points)
    if (dp < 0.2 && maxTime >= 6) {
        set<int> pts;
        while (pts.size() < 6) {
            pts.insert(rnd.next(1, maxTime));
        }
        vector<int> v(pts.begin(), pts.end());
        sort(v.begin(), v.end());
        for (int i = 0; i < 3; i++) {
            intervals.emplace_back(v[2*i], v[2*i + 1]);
        }
    }
    // Mode 2: full overlap intervals
    else if (dp < 0.4) {
        int L = rnd.next(1, maxTime - 1);
        int R = rnd.next(L + 1, maxTime);
        for (int i = 0; i < 3; i++) {
            int s = rnd.next(1, L);
            int e = rnd.next(R, maxTime);
            intervals.emplace_back(s, e);
        }
    }
    // Mode 3: fully random intervals
    else {
        for (int i = 0; i < 3; i++) {
            int s = rnd.next(1, maxTime - 1);
            int e = rnd.next(s + 1, maxTime);
            intervals.emplace_back(s, e);
        }
    }

    // Shuffle their order
    shuffle(intervals.begin(), intervals.end());

    // Output
    println(A, B, C);
    for (auto &p : intervals) {
        println(p.first, p.second);
    }
    return 0;
}
