#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 60);
    } else if (mode == 4) {
        n = rnd.next(61, 100);
    } else {
        n = 100;
    }

    vector<int> pool;
    if (mode == 0 || mode == 5) {
        pool = {-100, -1, 0, 1, 100};
    } else {
        int lo = rnd.next(-100, 80);
        int hi = rnd.next(lo, 100);
        for (int x = lo; x <= hi; ++x) {
            pool.push_back(x);
        }
    }

    int v = rnd.any(pool);
    vector<int> a(n);

    int pattern = rnd.next(0, 4);
    if (pattern == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = v;
        }
    } else if (pattern == 1) {
        int other = v;
        while (other == v) {
            other = rnd.next(-100, 100);
        }
        for (int i = 0; i < n; ++i) {
            a[i] = other;
        }
    } else {
        int targetCount;
        if (pattern == 2) {
            targetCount = rnd.next(1, n);
        } else if (pattern == 3) {
            targetCount = min(n, rnd.next(1, 3));
        } else {
            targetCount = max(0, n - rnd.next(1, min(n, 3)));
        }

        for (int i = 0; i < targetCount; ++i) {
            a[i] = v;
        }
        for (int i = targetCount; i < n; ++i) {
            int x = v;
            while (x == v) {
                x = rnd.any(pool);
                if (pool.size() == 1) {
                    x = (v == 100 ? 99 : v + 1);
                }
            }
            a[i] = x;
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    println(v);

    return 0;
}
