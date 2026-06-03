#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int k;
    if (mode == 0) {
        k = n;
    } else if (mode == 1) {
        k = 1;
    } else {
        k = rnd.next(1, n);
    }

    vector<int> pool = {0};
    int poolSize = rnd.next(3, 7);
    int cap = rnd.any(vector<int>{20, 100, 1000, 1000000});
    for (int i = 1; i < poolSize; ++i) {
        pool.push_back(rnd.next(0, cap));
    }
    sort(pool.begin(), pool.end());
    pool.erase(unique(pool.begin(), pool.end()), pool.end());

    println(n, k);
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        if (mode == 2) {
            int base = rnd.any(pool);
            int spread = rnd.next(0, min(25, 1000000 - base));
            a = base;
            b = base + rnd.next(0, spread);
            c = base + rnd.next(0, spread);
        } else if (mode == 3) {
            a = rnd.next(0, 1000000);
            b = rnd.next(0, 10);
            c = rnd.next(0, 10);
        } else if (mode == 4) {
            a = rnd.any(pool);
            b = rnd.any(pool);
            c = rnd.any(pool);
        } else if (mode == 5) {
            int high = rnd.next(999990, 1000000);
            a = rnd.next(0, 10);
            b = rnd.next(0, 10);
            c = high;
            if (rnd.next(0, 1)) swap(a, c);
            if (rnd.next(0, 1)) swap(b, c);
        } else {
            a = rnd.next(0, cap);
            b = rnd.next(0, cap);
            c = rnd.next(0, cap);
        }
        println(a, b, c);
    }

    return 0;
}
