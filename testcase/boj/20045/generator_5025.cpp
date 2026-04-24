#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkable
    int n = rnd.next(1, 10);
    int maxSubs = n * (n + 1) / 2;
    int k = rnd.next(1, maxSubs);

    // Choose a distribution type for diversity
    // 0: mixed [-10,10]
    // 1: non-negative [0,10]
    // 2: non-positive [-10,0]
    // 3: mixed sorted ascending
    // 4: mixed sorted descending
    int type = rnd.next(0, 4);

    vector<int> a(n);
    if (type <= 2) {
        int lo = (type == 1 ? 0 : -10);
        int hi = (type == 2 ? 0 : 10);
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(lo, hi);
        }
    } else {
        // mixed in [-10,10] then sort
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(-10, 10);
        }
        if (type == 3) {
            sort(a.begin(), a.end());
        } else {
            sort(a.begin(), a.end(), greater<int>());
        }
    }

    // Output
    println(n, k);
    println(a);

    return 0;
}
