#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of problems n: skewed to small or large values
    int n;
    if (rnd.next(0,1) == 0) n = rnd.wnext(10, 3) + 1;  // skew high
    else             n = rnd.wnext(10, -3) + 1;         // skew low
    // Balloon lifespan d: either small or moderate
    int d = (rnd.next(0,1) == 0 ? rnd.next(1,5) : rnd.next(6,20));
    // Maximum solve time to sample s_i
    int maxSolve = (rnd.next(0,1) == 0 ? rnd.next(1,5) : rnd.next(6,20));
    // Generate solve times with varied distributions
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        int pat = rnd.next(0,2);
        if (pat == 0) {
            // uniform
            s[i] = rnd.next(1, maxSolve);
        } else if (pat == 1) {
            // skew small
            s[i] = rnd.wnext(maxSolve, -2) + 1;
        } else {
            // skew large
            s[i] = rnd.wnext(maxSolve, 2) + 1;
        }
    }
    // Sometimes sort the times, sometimes shuffle
    if (rnd.next(0,1)) sort(s.begin(), s.end());
    else shuffle(s.begin(), s.end());
    // Dice mass m: sometimes possible (<=n), sometimes impossible (>n)
    int m;
    if (rnd.next(0,1) == 0) {
        // ensure potentially solvable
        m = rnd.next(1, n);
    } else {
        // force impossible by exceeding max balloons
        m = rnd.next(n+1, n+3);
    }
    // Output
    println(n, d, m);
    println(s);
    return 0;
}
