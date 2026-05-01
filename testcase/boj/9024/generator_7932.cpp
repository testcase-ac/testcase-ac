#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int t = rnd.next(1, 4);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        // Choose n: sometimes minimal, otherwise up to 15
        int n;
        if (rnd.next(0, 4) == 0) {
            n = 2;
        } else {
            n = rnd.next(3, 15);
        }
        // Distribution regime: 0=all positive, 1=all negative, 2=mixed
        int regime = rnd.next(0, 2);
        int M;
        if (regime == 2) {
            // mixed: span from -(n+1)/2..(n+1)/2 up to 20
            M = rnd.next((n + 1) / 2, 20);
        } else {
            // positive or negative: 1..20 but ensure >= n
            M = rnd.next(n, 20);
        }
        int lo, hi;
        if (regime == 0) {
            lo = 1; hi = M;
        } else if (regime == 1) {
            lo = -M; hi = -1;
        } else {
            lo = -M; hi = M;
        }
        // Generate n distinct numbers in [lo, hi]
        set<int> s;
        while ((int)s.size() < n) {
            s.insert(rnd.next(lo, hi));
        }
        vector<int> v(s.begin(), s.end());
        shuffle(v.begin(), v.end());
        // Compute minimal and maximal possible sums
        vector<int> w = v;
        sort(w.begin(), w.end());
        int sum_min = w[0] + w[1];
        int sum_max = w[n - 1] + w[n - 2];
        // Choose K regime: below, above, exact pair sum, or random inside
        int regK = rnd.next(0, 3);
        int K;
        if (regK == 0) {
            int delta = rnd.next(1, 10);
            K = sum_min - delta;
        } else if (regK == 1) {
            int delta = rnd.next(1, 10);
            K = sum_max + delta;
        } else if (regK == 2) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 2);
            if (j >= i) j++;
            K = v[i] + v[j];
        } else {
            K = rnd.next(sum_min, sum_max);
        }
        // Output test case
        println(n, K);
        println(v);
    }
    return 0;
}
