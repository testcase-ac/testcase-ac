#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of tasks
    int n = rnd.next(1, 10);
    // choose heavy or light tasks
    bool heavy = rnd.next(0, 1);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (heavy)
            a[i] = rnd.next(20, 100);
        else
            a[i] = rnd.next(1, 20);
    }
    // optionally sort tasks to create special patterns
    int orderType = rnd.next(0, 2);
    if (orderType == 1) {
        sort(a.begin(), a.end());
    } else if (orderType == 2) {
        sort(a.begin(), a.end(), greater<int>());
    }
    // compute sums
    int total = accumulate(a.begin(), a.end(), 0);
    int min_a = *min_element(a.begin(), a.end());
    // choose budget mode: small, medium, large
    int mode = rnd.next(0, 2);
    int T;
    if (mode == 0) {
        // small budget, maybe zero tasks
        int hi = min(min_a - 1, 500);
        if (hi >= 1)
            T = rnd.next(1, hi);
        else
            T = 1;
    } else if (mode == 1) {
        // medium budget, between 1 and total-1
        int hi = min(total - 1, 500);
        if (hi >= 1)
            T = rnd.next(1, hi);
        else
            T = 1;
    } else {
        // large budget, at least total
        if (total < 500) {
            T = rnd.next(total, min(total + 50, 500));
        } else {
            T = 500;
        }
    }
    // output
    println(n, T);
    println(a);
    return 0;
}
