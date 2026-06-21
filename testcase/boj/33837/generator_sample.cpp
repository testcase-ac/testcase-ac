#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int valueWithGcd(int base, int maxMultiplier) {
    return base * rnd.next(1, maxMultiplier);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 3);
        int x = rnd.next(1, 5000);
        a.assign(n, x);
    } else if (mode == 1) {
        int n = rnd.next(2, 24);
        int g1 = rnd.next(1, 100);
        int g2 = rnd.next(1, 100);
        int split = rnd.next(1, n - 1);

        for (int i = 0; i < split; ++i) {
            a.push_back(valueWithGcd(g1, 5000 / g1));
        }
        for (int i = split; i < n; ++i) {
            a.push_back(valueWithGcd(g2, 5000 / g2));
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 30);
        int common = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 5000 / common);
            if (rnd.next(0, 3) == 0) {
                multiplier = rnd.next(1, 8);
            }
            a.push_back(common * multiplier);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 30);
        vector<int> pool;
        int poolSize = rnd.next(2, 8);
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(1, 5000));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        int n = rnd.next(2, 30);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, min(5000, lo + rnd.next(0, 250)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
