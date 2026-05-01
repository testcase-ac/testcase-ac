#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for n: small, medium, larger but hand-checkable
    int nMode = rnd.next(0, 2);
    int n;
    if (nMode == 0)      n = rnd.next(2, 6);
    else if (nMode == 1) n = rnd.next(7, 15);
    else                 n = rnd.next(16, 30);

    int maxk = n / 2;
    // Hyperparameter for k: relative to n
    int kMode = rnd.next(0, 2);
    int k;
    if (kMode == 0) {
        k = rnd.next(1, max(1, n / 5));
    } else if (kMode == 1) {
        int lo = max(1, n / 5 + 1);
        int hi = maxk - 1;
        if (lo <= hi) k = rnd.next(lo, hi);
        else          k = rnd.next(1, maxk);
    } else {
        k = rnd.next(max(1, maxk - 1), maxk);
    }

    // Generate sorted distinct positions
    vector<long long> s;
    int posMode = rnd.next(0, 2);
    if (posMode == 0) {
        // Uniform random distinct points
        set<long long> st;
        while ((int)st.size() < n) {
            st.insert(rnd.next(0LL, 1000000000LL));
        }
        s.assign(st.begin(), st.end());
    }
    else if (posMode == 1) {
        // Clustered points
        int c = rnd.next(1, min(n, 5));
        vector<int> sz(c, 1);
        for (int i = c; i < n; i++) {
            sz[rnd.next(0, c - 1)]++;
        }
        vector<long long> bases(c);
        long long curr = 0;
        for (int i = 0; i < c; i++) {
            curr += rnd.next(1LL, 100LL);
            bases[i] = curr;
        }
        for (int i = 0; i < c; i++) {
            for (int j = 0; j < sz[i]; j++) {
                long long off = rnd.next(0LL, (long long)min(n, 100));
                s.push_back(bases[i] + off);
            }
        }
    }
    else {
        // Arithmetic progression
        long long start = rnd.next(0LL, 100LL);
        long long step  = rnd.next(1LL, 100LL);
        for (int i = 0; i < n; i++) {
            s.push_back(start + step * i);
        }
    }

    // Ensure we have exactly n distinct sorted points
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    while ((int)s.size() < n) {
        long long x = rnd.next(0LL, 1000000000LL);
        if (!binary_search(s.begin(), s.end(), x))
            s.push_back(x);
    }
    sort(s.begin(), s.end());

    // Output
    println(n, k);
    for (auto x : s) println(x);

    return 0;
}
