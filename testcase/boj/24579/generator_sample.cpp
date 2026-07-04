#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int p;
    int k;

    if (mode == 0) {
        n = 1;
        p = rnd.next(1, 20);
        k = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        p = rnd.next(1, 12);
        k = rnd.next(1, 15);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        p = rnd.next(10, 60);
        k = rnd.next(1, 30);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        p = rnd.any(vector<int>{1, 2, 3, 10, 1000000000});
        k = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        p = rnd.next(20, 200);
        k = rnd.next(1, 1000);
    } else {
        n = rnd.next(2, 14);
        p = rnd.next(1, 1000000000);
        k = rnd.any(vector<int>{1, 2, 3, 1000000000});
    }

    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        int pattern = rnd.next(0, 5);
        if (pattern == 0) {
            d[i] = 1;
        } else if (pattern == 1) {
            d[i] = p;
        } else if (pattern == 2) {
            d[i] = (p + 1) / 2;
        } else if (pattern == 3) {
            int hi = min(p, 20);
            d[i] = rnd.next(1, hi);
        } else if (pattern == 4) {
            int lo = max(1, p - min(p - 1, 20));
            d[i] = rnd.next(lo, p);
        } else {
            d[i] = rnd.next(1, p);
        }
    }

    if (mode == 1) {
        sort(d.begin(), d.end());
    } else if (mode == 2) {
        sort(d.rbegin(), d.rend());
    } else if (mode == 4) {
        shuffle(d.begin(), d.end());
    }

    println(n, p, k);
    for (int x : d) {
        println(x);
    }

    return 0;
}
