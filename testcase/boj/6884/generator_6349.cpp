#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

bool isComposite(int x) {
    if (x < 2) return true;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small primes for sums
    vector<int> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    // primes p>=11 with p-2 composite, for length-3-only case
    vector<int> triplePrimes = {11,17,23,29,37,41,47};
    // composite-ish values for anti-primed
    vector<int> compVals = {0,4,6,8,9,10};

    int T = rnd.next(5, 10);
    printf("%d\n", T);
    for (int tc = 0; tc < T; ++tc) {
        int strat = rnd.wnext(3, 2); // 0..3 biased to 3
        int n;
        vector<int> a;
        if (strat == 0) {
            // trivial two-sum prime at start
            n = rnd.next(5, 10);
            a.assign(n, 0);
            int p = rnd.any(smallPrimes);
            int x = rnd.next(0, p);
            a[0] = x;
            a[1] = p - x;
            for (int i = 2; i < n; ++i)
                a[i] = rnd.next(0, 10);
        } else if (strat == 1) {
            // minimal length 3: first pair composite, triple sum prime
            n = rnd.next(5, 10);
            a.assign(n, 0);
            int p = rnd.any(triplePrimes);
            // fix a[0]=2,a[1]=2 sum=4 composite
            a[0] = 2; a[1] = 2;
            a[2] = p - 4; // ensures triple sum = p
            for (int i = 3; i < n; ++i)
                a[i] = rnd.next(0, 10);
        } else if (strat == 2) {
            // anti-primed: no prime-sum subseq
            n = rnd.next(5, 8);
            a.assign(n, 0);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.any(compVals);
        } else {
            // random-general
            n = rnd.next(3, 10);
            a.assign(n, 0);
            if (rnd.next() < 0.5) {
                // force one prime-sum pair at random position
                int pos = rnd.next(0, n - 2);
                int p = rnd.any(smallPrimes);
                int x = rnd.next(0, p);
                for (int i = 0; i < n; ++i) {
                    if (i == pos) a[i] = x;
                    else if (i == pos + 1) a[i] = p - x;
                    else a[i] = rnd.next(0, 10);
                }
            } else {
                // fully random
                for (int i = 0; i < n; ++i)
                    a[i] = rnd.next(0, 10);
            }
        }
        // output this test case
        printf("%d", n);
        for (int i = 0; i < n; ++i)
            printf(" %d", a[i]);
        printf("\n");
    }
    return 0;
}
