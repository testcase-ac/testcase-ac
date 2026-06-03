#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> d;

    if (mode == 0) {
        n = rnd.next(2, 20);
        d.assign(n, rnd.next(1, 10000));
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        int a = rnd.next(1, 10000);
        int b = rnd.next(1, 10000);
        while (b == a) b = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(0, 3) == 0 ? b : a);
    } else if (mode == 2) {
        n = rnd.next(2, 60);
        int lo = rnd.next(1, 9950);
        int width = rnd.next(0, min(50, 10000 - lo));
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(lo, lo + width));
    } else if (mode == 3) {
        n = rnd.next(2, 80);
        int start = rnd.next(1, 10000 - n + 1);
        for (int i = 0; i < n; ++i) d.push_back(start + i);
        shuffle(d.begin(), d.end());
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(0, 1) ? rnd.next(1, 5) : rnd.next(9996, 10000));
    } else if (mode == 5) {
        n = rnd.next(2, 120);
        int distinct = rnd.next(2, min(n, 12));
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int value = rnd.next(1, 10000);
            if (find(pool.begin(), pool.end(), value) == pool.end()) pool.push_back(value);
        }
        for (int i = 0; i < n; ++i) d.push_back(rnd.any(pool));
    } else if (mode == 6) {
        n = rnd.next(2, 150);
        for (int i = 0; i < n; ++i) d.push_back(rnd.wnext(10000, rnd.next(-3, 3)) + 1);
    } else {
        n = rnd.next(1000, 3000);
        int distinct = rnd.next(2, 30);
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int value = rnd.next(1, 10000);
            if (find(pool.begin(), pool.end(), value) == pool.end()) pool.push_back(value);
        }
        for (int i = 0; i < n; ++i) d.push_back(rnd.any(pool));
    }

    println(n);
    println(d);

    return 0;
}
