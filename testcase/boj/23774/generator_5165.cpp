#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of slices
    int n = rnd.next(3, 10);
    vector<long long> s(n);
    // pattern type for diversity
    int type = rnd.next(0, 3);
    if (type == 0) {
        // purely random small spiciness
        for (int i = 0; i < n; i++)
            s[i] = rnd.next(0LL, 100LL);
    } else if (type == 1) {
        // single peak pattern
        int p = rnd.next(0, n - 1);
        for (int i = 0; i < n; i++) {
            if (i <= p)
                s[i] = (long long)i * 10 + rnd.next(0, 5);
            else
                s[i] = (long long)(n - 1 - i) * 10 + rnd.next(0, 5);
        }
    } else if (type == 2) {
        // mostly zeros with one moderate peak
        fill(s.begin(), s.end(), 0LL);
        int j = rnd.next(0, n - 1);
        s[j] = rnd.next(50LL, 200LL);
    } else {
        // descending sequence with occasional local swaps
        for (int i = 0; i < n; i++)
            s[i] = rnd.next(0LL, 100LL);
        sort(s.begin(), s.end(), greater<long long>());
        for (int i = 0; i + 1 < n; i++)
            if (rnd.next() < 0.3)
                swap(s[i], s[i + 1]);
    }
    // inject one large spike occasionally
    if (rnd.next() < 0.3) {
        const long long LMIN = 1000000000000LL;
        const long long LMAX = 10000000000000LL;
        int j = rnd.next(0, n - 1);
        s[j] = rnd.next(LMIN, LMAX);
    }
    // random cyclic rotation
    if (rnd.next() < 0.5) {
        int shift = rnd.next(0, n - 1);
        rotate(s.begin(), s.begin() + shift, s.end());
    }
    // output
    println(n);
    println(s);
    return 0;
}
