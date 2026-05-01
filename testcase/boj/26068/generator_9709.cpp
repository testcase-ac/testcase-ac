#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose scenario type for diversity
    int type = rnd.next(0, 6);
    int N = 0;
    vector<int> xs;

    if (type == 0) {
        // Very small N, fully random x
        N = rnd.next(1, 5);
        xs.resize(N);
        for (int i = 0; i < N; ++i)
            xs[i] = rnd.next(1, 365);
    } else if (type == 1) {
        // Medium N, roughly half usable (<=90), half not (>90)
        N = rnd.next(10, 30);
        int k1 = N / 2;
        int k2 = N - k1;
        for (int i = 0; i < k1; ++i) {
            int kind = rnd.next(0, 2);
            if (kind == 0) xs.push_back(90);
            else if (kind == 1) xs.push_back(1);
            else xs.push_back(rnd.next(1, 90));
        }
        for (int i = 0; i < k2; ++i) {
            int kind = rnd.next(0, 2);
            if (kind == 0) xs.push_back(91);
            else if (kind == 1) xs.push_back(365);
            else xs.push_back(rnd.next(91, 365));
        }
        shuffle(xs.begin(), xs.end());
    } else if (type == 2) {
        // Boundary heavy: lots of 90 and 91, plus a few extremes
        N = rnd.next(10, 25);
        for (int i = 0; i < N; ++i) {
            int which = rnd.next(0, 4);
            if (which == 0) xs.push_back(90);
            else if (which == 1) xs.push_back(91);
            else if (which == 2) xs.push_back(1);
            else xs.push_back(365);
        }
        shuffle(xs.begin(), xs.end());
    } else if (type == 3) {
        // All usable: all <= 90
        N = rnd.next(5, 40);
        xs.resize(N);
        for (int i = 0; i < N; ++i)
            xs[i] = rnd.next(1, 90);
    } else if (type == 4) {
        // None usable: all > 90
        N = rnd.next(5, 40);
        xs.resize(N);
        for (int i = 0; i < N; ++i)
            xs[i] = rnd.next(91, 365);
    } else if (type == 5) {
        // Random N, mixed distribution skewed to extremes sometimes
        N = rnd.next(1, 70);
        xs.resize(N);
        for (int i = 0; i < N; ++i) {
            if (rnd.next(0, 1) == 0) {
                xs[i] = rnd.next(1, 365);
            } else {
                // Bias towards smaller or larger values
                int hi = 365;
                int t = rnd.next(-3, 3); // some skew
                int v = rnd.wnext(hi, t);
                xs[i] = max(1, min(365, v + 1));
            }
        }
    } else { // type == 6
        // Explicit threshold-test case, must contain 89, 90, 91
        N = rnd.next(3, 10);
        xs.push_back(89);
        xs.push_back(90);
        xs.push_back(91);
        while ((int)xs.size() < N) {
            int kind = rnd.next(0, 3);
            if (kind == 0) xs.push_back(rnd.next(1, 90));
            else if (kind == 1) xs.push_back(rnd.next(91, 365));
            else xs.push_back(90);
        }
        shuffle(xs.begin(), xs.end());
    }

    // Safety: if N not explicitly set in a branch (shouldn't happen), fix it.
    if (N == 0) N = (int)xs.size();
    if ((int)xs.size() != N) xs.resize(N);

    println(N);
    for (int i = 0; i < N; ++i) {
        string s = "D-" + to_string(xs[i]);
        println(s);
    }

    return 0;
}
