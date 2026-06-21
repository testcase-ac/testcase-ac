#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(0, 1000000000));
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        int x = rnd.next(0, 1000000000);
        a.assign(n, x);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) ? 1000000000 : 0);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        int lo = rnd.next(0, 50);
        int hi = rnd.next(lo, min(100, lo + rnd.next(0, 50)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        vector<int> pool;
        int poolSize = rnd.next(2, 5);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(0, 1000000000));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(0, 100));
            } else {
                a.push_back(rnd.next(999999900, 1000000000));
            }
        }
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1000000000));
        }
    }

    if (rnd.next(0, 2) == 0) {
        sort(a.begin(), a.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(a.rbegin(), a.rend());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
