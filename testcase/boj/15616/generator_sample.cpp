#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxA = 2000000;
    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 20);
        int x = rnd.next(1, maxA);
        a.assign(n, x);
    } else if (mode == 1) {
        int base = rnd.next(1, 1000);
        int cur = base;
        while (cur <= maxA && (int)a.size() < rnd.next(6, 18)) {
            int copies = rnd.next(1, 3);
            for (int i = 0; i < copies; ++i) a.push_back(cur);
            if (cur > maxA / 2) break;
            cur *= rnd.next(2, 4);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 24);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(1);
            } else if (i % 3 == 1) {
                a.push_back(maxA);
            } else {
                a.push_back(rnd.next(maxA - 30, maxA));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 30);
        int poolSize = rnd.next(2, 7);
        vector<int> pool;
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, 80));
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 4) {
        int n = rnd.next(5, 25);
        int step = rnd.next(1, 20);
        int start = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) a.push_back(start + i * step);
    } else {
        int n = rnd.next(1, 35);
        int lo = rnd.next(1, 200);
        int hi = rnd.next(lo, min(maxA, lo + rnd.next(0, 5000)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);
    return 0;
}
