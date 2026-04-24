#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);

    vector<int> a(n), b(m);

    // Hyperparameter: distribution type (0 = uniform, 1 = clustered)
    int distType = rnd.next(0, 1);
    if (distType == 0) {
        // Uniform distribution in [1,100]
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(1, 100);
        for (int i = 0; i < m; i++)
            b[i] = rnd.next(1, 100);
    } else {
        // Clustered distribution: two cluster centers and a spread
        int d = rnd.next(0, 20);
        int c1 = rnd.next(1, 100);
        int c2 = rnd.next(1, 100);
        int lo1 = max(1, c1 - d), hi1 = min(100, c1 + d);
        int lo2 = max(1, c2 - d), hi2 = min(100, c2 + d);
        for (int i = 0; i < n; i++) {
            if (rnd.next(0,1) == 0)
                a[i] = rnd.next(lo1, hi1);
            else
                a[i] = rnd.next(lo2, hi2);
        }
        for (int i = 0; i < m; i++) {
            if (rnd.next(0,1) == 0)
                b[i] = rnd.next(lo1, hi1);
            else
                b[i] = rnd.next(lo2, hi2);
        }
    }

    // Hyperparameter: ordering (0=random, 1=sorted asc, 2=sorted desc)
    int ord = rnd.next(0, 2);
    if (ord == 1) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
    } else if (ord == 2) {
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end(), greater<int>());
    }
    
    // Output
    println(n, m);
    println(a);
    println(b);

    return 0;
}
