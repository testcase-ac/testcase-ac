#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int exp;
    int n;
    int m;
    int k;

    if (mode == 0) {
        exp = rnd.next(1, 4);
        n = 1 << exp;
        m = rnd.next(0, n);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        exp = rnd.next(1, 18);
        n = 1 << exp;
        vector<int> candidates = {1, n};
        if (n >= 4) {
            candidates.push_back(n / 2);
            candidates.push_back(n / 2 + 1);
        }
        k = rnd.any(candidates);
        m = rnd.any(vector<int>{0, 1, min(n, exp), max(0, n - 1), n});
    } else if (mode == 2) {
        exp = rnd.next(5, 18);
        n = 1 << exp;
        m = rnd.next(0, min(n, 8));
        k = rnd.next(1, min(n, 32));
    } else if (mode == 3) {
        exp = rnd.next(5, 18);
        n = 1 << exp;
        m = rnd.next(max(0, n - 8), n);
        k = rnd.next(max(1, n - 31), n);
    } else if (mode == 4) {
        exp = rnd.next(2, 18);
        n = 1 << exp;
        int pivotExp = rnd.next(0, exp);
        int pivot = 1 << pivotExp;
        int lo = max(1, pivot - 2);
        int hi = min(n, pivot + 2);
        k = rnd.next(lo, hi);
        m = rnd.next(0, min(n, exp + 3));
    } else if (mode == 5) {
        exp = rnd.next(1, 18);
        n = 1 << exp;
        k = rnd.next(1, n);
        m = rnd.next(0, min(n, 2 * exp + 1));
    } else if (mode == 6) {
        exp = rnd.next(1, 18);
        n = 1 << exp;
        k = rnd.next(1, n);
        m = rnd.next(max(0, n - 2 * exp - 1), n);
    } else {
        exp = rnd.next(1, 18);
        n = 1 << exp;
        k = rnd.next(1, n);
        m = rnd.next(0, n);
    }

    println(n, m, k);
    return 0;
}
