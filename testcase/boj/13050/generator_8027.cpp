#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes: small enough to manually check, but variable
    int n = rnd.next(1, 20);
    int m = rnd.next(1, 20);

    // Hyper-parameter: distribution type for a[]
    int dt = rnd.next(0, 2);
    vector<int> a(n);
    if (dt == 0) {
        // small values
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(-5, 5);
    } else if (dt == 1) {
        // wide range
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(-100, 100);
    } else {
        // clustered around random centers
        int k = rnd.next(1, min(4, n));
        vector<int> centers(k);
        for (int i = 0; i < k; i++)
            centers[i] = rnd.next(-50, 50);
        for (int i = 0; i < n; i++) {
            int c = rnd.any(centers);
            a[i] = c + rnd.next(-10, 10);
        }
    }

    // Hyper-parameter: ordering of a[]
    int ot = rnd.next(0, 3);
    if (ot == 1) {
        shuffle(a.begin(), a.end());
    } else if (ot == 2) {
        sort(a.begin(), a.end());
    } else if (ot == 3) {
        sort(a.begin(), a.end(), greater<int>());
    }
    // else ot==0: keep as generated

    // Compute min and max of a[]
    int amin = *min_element(a.begin(), a.end());
    int amax = *max_element(a.begin(), a.end());

    // Generate b[] with several scenarios
    vector<int> b(m);
    for (int j = 0; j < m; j++) {
        int s = rnd.next(0, 3);
        if (s == 0) {
            // exactly equal to some a[i]
            b[j] = rnd.any(a);
        } else if (s == 1) {
            // a value within [amin, amax]
            b[j] = rnd.next(amin, amax);
        } else if (s == 2) {
            // greater than all a => expect 0
            b[j] = amax + rnd.next(1, 20);
        } else {
            // less than all a => segment can be whole array
            b[j] = amin - rnd.next(1, 20);
        }
    }

    // Output
    println(n, m);
    println(a);
    println(b);

    return 0;
}
