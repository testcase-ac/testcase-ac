#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper‐parameter for n: skew towards small/medium/large
    vector<int> tvals = {-2, 0, 2};
    int tval = rnd.any(tvals);
    int n = rnd.wnext(15, tval) + 1; // n in [1,15]

    // Route length l just above n
    int l = n + 1 + rnd.next(1, 20); // l in [n+2, n+21]

    // Generate n distinct stop positions in (0, l)
    vector<int> pos;
    for (int i = 1; i < l; i++) pos.push_back(i);
    shuffle(pos.begin(), pos.end());
    pos.resize(n);
    sort(pos.begin(), pos.end());

    // Generate waiting times with a mixture of zero, small, and larger values
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        double p = rnd.next();
        if (p < 0.2) {
            w[i] = 0;
        } else if (p < 0.6) {
            w[i] = rnd.next(1, 3);
        } else {
            int low = l / 2;
            int high = l * 2;
            w[i] = rnd.next(low, high);
        }
    }

    // Choose max running speed v with varied regimes
    double p2 = rnd.next();
    int v;
    if (p2 < 0.3) {
        v = 1;
    } else if (p2 < 0.6) {
        v = rnd.next(2, 5);
    } else {
        v = rnd.next(6, 20);
    }

    // Output in required format
    println(n, l);
    println(pos);
    println(w);
    println(v);

    return 0;
}
