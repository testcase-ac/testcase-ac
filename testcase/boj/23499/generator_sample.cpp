#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int maxPairs(int n) {
    return n * (n - 1) / 2;
}

int triangular(int t) {
    return t * (t - 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;
    int x;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(0, maxPairs(n));
        x = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 60);
        k = 0;
        x = rnd.next(2, 1000);
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        k = maxPairs(n);
        x = rnd.next(2, 1000);
    } else if (mode == 3) {
        n = rnd.next(2, 120);
        int cap = maxPairs(n);
        int edge = min(cap, rnd.next(1, min(30, cap)));
        k = rnd.next(2) == 0 ? edge : cap - edge;
        x = rnd.next(2, 1000);
    } else if (mode == 4) {
        int t = rnd.next(2, 44);
        n = rnd.next(t, min(1000, t + 30));
        k = triangular(t);
        if (rnd.next(3) == 0 && k < maxPairs(n)) {
            k += rnd.next(1, min(10, maxPairs(n) - k));
        }
        x = rnd.next(2, 1000);
    } else if (mode == 5) {
        n = rnd.next(50, 300);
        int cap = maxPairs(n);
        k = rnd.wnext(cap + 1, rnd.next(2) == 0 ? -3 : 3);
        x = rnd.next(2, 1000);
    } else if (mode == 6) {
        n = rnd.next(900, 1000);
        int cap = maxPairs(n);
        k = rnd.any(vector<int>{0, 1, cap / 2, cap - 1, cap});
        x = rnd.next(2, 1000);
    } else {
        n = rnd.next(1, 1000);
        k = rnd.next(0, maxPairs(n));
        x = rnd.any(vector<int>{2, 3, 999, 1000});
    }

    println(n, k, x);
    return 0;
}
