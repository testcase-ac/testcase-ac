#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int n = rnd.next(4, 10);
        bool wantWeak = rnd.next(0, 1);
        vector<int> A(n, 0);
        if (wantWeak) {
            // choose pattern type: 0 = increasing pattern, 1 = decreasing pattern
            int pat = rnd.next(0, 1);
            // choose positions 1 <= p < q < r < s <= n
            int p = rnd.next(1, n - 3);
            int q = rnd.next(p + 1, n - 2);
            int r = rnd.next(q + 1, n - 1);
            int s = rnd.next(r + 1, n);
            // generate base values so that A values are distinct and within [1,10000]
            int maxBase = 10000 - (n - 1);
            int base = rnd.next(1, maxBase);
            vector<int> vals(n);
            for (int i = 0; i < n; i++) {
                vals[i] = base + i;
            }
            vector<int> rest;
            if (pat == 0) {
                // increasing pattern: vals[0] < vals[1] < vals[2] < vals[3]
                A[q-1] = vals[0];
                A[s-1] = vals[1];
                A[p-1] = vals[2];
                A[r-1] = vals[3];
                // rest are vals[4..]
                for (int i = 4; i < n; i++) rest.push_back(vals[i]);
            } else {
                // decreasing pattern: vals[n-1] > vals[n-2] > vals[n-3] > vals[n-4]
                A[q-1] = vals[n-1];
                A[s-1] = vals[n-2];
                A[p-1] = vals[n-3];
                A[r-1] = vals[n-4];
                // rest are vals[0..n-5]
                for (int i = 0; i < n-4; i++) rest.push_back(vals[i]);
            }
            // fill other positions
            shuffle(rest.begin(), rest.end());
            int idx = 0;
            for (int i = 0; i < n; i++) {
                if (A[i] == 0) {
                    A[i] = rest[idx++];
                }
            }
        } else {
            // non-weak: simple monotonic sequence
            if (rnd.next(0,1) == 0) {
                // ascending
                for (int i = 0; i < n; i++) A[i] = i + 1;
            } else {
                // descending
                for (int i = 0; i < n; i++) A[i] = n - i;
            }
        }
        println(n);
        println(A);
    }
    return 0;
}
