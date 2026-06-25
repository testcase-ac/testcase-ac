#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = 1;
    vector<int> a;

    if (mode == 0) {
        m = rnd.next(1, 20);
        a.push_back(rnd.next(0, (1 << m) - 1));
    } else if (mode == 1) {
        m = rnd.next(2, 8);
        int upper = 1 << m;
        int n = rnd.next(2, min(24, upper));
        int base = rnd.next(0, upper - 1);
        int mask = upper - 1;
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(base);
            } else if (i % 3 == 1) {
                a.push_back(base ^ mask);
            } else {
                a.push_back(rnd.next(0, upper - 1));
            }
        }
    } else if (mode == 2) {
        m = rnd.next(1, 6);
        int upper = 1 << m;
        a.resize(upper);
        for (int i = 0; i < upper; ++i) {
            a[i] = i;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        m = rnd.next(3, 12);
        int upper = 1 << m;
        int n = rnd.next(3, min(32, upper));
        int center = rnd.next(0, upper - 1);
        int lowBits = rnd.next(1, min(m, 5));
        int localMask = (1 << lowBits) - 1;
        for (int i = 0; i < n; ++i) {
            a.push_back((center & ~localMask) | rnd.next(0, localMask));
        }
    } else if (mode == 4) {
        m = rnd.next(1, 10);
        int upper = 1 << m;
        int distinct = rnd.next(1, min(8, upper));
        int n = rnd.next(distinct, min(40, upper));
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int x = rnd.next(0, upper - 1);
            if (find(pool.begin(), pool.end(), x) == pool.end()) {
                pool.push_back(x);
            }
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        m = rnd.next(16, 20);
        int upper = 1 << m;
        int n = rnd.next(2, 50);
        a.push_back(0);
        a.push_back(upper - 1);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(0, upper - 1));
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size(), m);
    println(a);
    return 0;
}
