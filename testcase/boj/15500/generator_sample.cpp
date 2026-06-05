#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 4);
        a.assign(n, rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        a.resize(n);
        iota(a.begin(), a.end(), 1);
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        a.resize(n);
        iota(a.begin(), a.end(), 1);
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 4) {
        n = rnd.next(5, 40);
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? x : y);
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        int distinct = rnd.next(1, min(n, 6));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, n));
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 6) {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(3) == 0 ? rnd.next(1, min(n, 5)) : rnd.next(1, n);
            a.push_back(value);
        }
    } else {
        n = rnd.next(80, 123);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(4) == 0 ? n : rnd.next(1, n);
            a.push_back(value);
        }
    }

    println(n);
    println(a);

    return 0;
}
