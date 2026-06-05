#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;
    vector<int> xs;

    if (mode == 0) {
        n = rnd.next(1, 12);
        q = rnd.next(1, 24);
        int x = rnd.next(1, n);
        xs.assign(q, x);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        q = rnd.next(1, n);
        xs.resize(n);
        for (int i = 0; i < n; ++i) xs[i] = i + 1;
        shuffle(xs.begin(), xs.end());
        xs.resize(q);
    } else if (mode == 2) {
        n = rnd.next(10, 80);
        q = rnd.next(1, 50);
        int residue = rnd.next(1, min(n, 10));
        for (int x = residue; x <= n; x += 10) xs.push_back(x);
        while ((int)xs.size() < q) xs.push_back(rnd.any(xs));
        shuffle(xs.begin(), xs.end());
        xs.resize(q);
    } else if (mode == 3) {
        n = rnd.next(1, 100);
        q = rnd.next(1, 60);
        vector<int> pool = {1, n};
        if (n >= 2) {
            pool.push_back(2);
            pool.push_back(n - 1);
        }
        if (n >= 10) {
            pool.push_back(10);
            pool.push_back(n - n % 10);
        }
        for (int i = 0; i < q; ++i) xs.push_back(rnd.any(pool));
    } else if (mode == 4) {
        n = rnd.next(1, 200);
        q = rnd.next(1, 120);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < q; ++i) xs.push_back(rnd.next(lo, hi));
    } else {
        n = rnd.next(1, 300);
        q = rnd.next(1, 180);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 4) == 0) {
                xs.push_back(rnd.any(vector<int>{1, n}));
            } else {
                xs.push_back(rnd.next(1, n));
            }
        }
    }

    println(n, q);
    for (int x : xs) println(x);

    return 0;
}
