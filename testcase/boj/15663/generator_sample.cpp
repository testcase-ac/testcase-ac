#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m;
    vector<int> a;

    if (mode == 0) {
        m = rnd.next(1, n);
        int value = rnd.next(1, 10000);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, n);
        int groups = rnd.next(1, n - 1);
        vector<int> pool;
        while ((int)pool.size() < groups) {
            int value = rnd.next(1, 20);
            bool seen = false;
            for (int x : pool) seen |= x == value;
            if (!seen) pool.push_back(value);
        }
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = n;
        for (int i = 0; i < n; ++i) a.push_back(i + 1);
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(1, n);
        int base = rnd.next(9990, 10000 - n + 1);
        for (int i = 0; i < n; ++i) a.push_back(base + i);
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = 8;
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 10000));
    } else {
        n = rnd.next(3, 8);
        m = rnd.next(2, n);
        int low = rnd.next(1, 50);
        int high = rnd.next(low, min(10000, low + rnd.next(0, 8)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(low, high));
    }

    if (a.empty()) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 10000));
    }

    println(n, m);
    println(a);
    return 0;
}
