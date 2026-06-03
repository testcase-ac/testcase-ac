#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int pickFrom(const vector<int>& values) {
    return values[rnd.next((int)values.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    vector<int> a(n), b(n);

    if (mode == 0) {
        vector<int> pool;
        int distinct = rnd.next(1, min(n, 8));
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, 20));
        for (int i = 0; i < n; ++i) a[i] = pickFrom(pool);
        b = a;
        shuffle(b.begin(), b.end());
    } else if (mode == 1) {
        int split = rnd.next(0, n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 12);
            b[i] = rnd.next(13, 24);
        }
        for (int i = 0; i < split; ++i) b[i] = a[rnd.next(n)];
        shuffle(b.begin(), b.end());
    } else if (mode == 2) {
        int favoriteA = rnd.next(1, 1000000);
        int favoriteB = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            a[i] = (rnd.next(100) < 75 ? favoriteA : rnd.next(1, 1000000));
            b[i] = (rnd.next(100) < 75 ? favoriteB : rnd.next(1, 1000000));
        }
    } else if (mode == 3) {
        vector<int> edges = {1, 2, 3, 999998, 999999, 1000000};
        for (int i = 0; i < n; ++i) {
            a[i] = pickFrom(edges);
            b[i] = pickFrom(edges);
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 1000000 - 2 * n);
        for (int i = 0; i < n; ++i) {
            a[i] = base + i;
            b[i] = base + n + i;
        }
        int swaps = rnd.next(0, n);
        for (int i = 0; i < swaps; ++i) b[rnd.next(n)] = a[rnd.next(n)];
    } else {
        int distinct = rnd.next(1, min(n, 10));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, 1000000));
        for (int i = 0; i < n; ++i) {
            a[i] = pickFrom(pool);
            b[i] = rnd.next(100) < 60 ? pickFrom(pool) : rnd.next(1, 1000000);
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
