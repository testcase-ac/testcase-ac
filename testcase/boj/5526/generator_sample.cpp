#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedScore(int value) {
    return max(1, min(100000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<int> p;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 80);
        p.resize(n);
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.next(4, 24);
        m = rnd.next(20, 2000);
        vector<int> pool;
        int base = rnd.next(1, max(1, m / 4));
        pool.push_back(base);
        pool.push_back(boundedScore(base + rnd.next(0, 5)));
        pool.push_back(boundedScore(max(1, m / 2 - rnd.next(0, 10))));
        pool.push_back(boundedScore(max(1, m - rnd.next(0, 20))));
        for (int i = 0; i < n; ++i) p.push_back(rnd.any(pool));
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        m = rnd.next(50, 1000000);
        p.push_back(boundedScore(m));
        p.push_back(boundedScore(max(1, m - 1)));
        p.push_back(boundedScore(max(1, m / 2)));
        p.push_back(boundedScore(max(1, m / 2 + 1)));
        p.push_back(boundedScore(max(1, m / 4)));
        while ((int)p.size() < n) {
            int center = rnd.any(p);
            p.push_back(boundedScore(center + rnd.next(-7, 7)));
        }
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        m = rnd.next(100000000, 200000000);
        p.push_back(100000000);
        p.push_back(rnd.next(99999980, 100000000));
        p.push_back(rnd.next(1, 30));
        while ((int)p.size() < n) {
            if (rnd.next(0, 1) == 0) {
                p.push_back(rnd.next(99999000, 100000000));
            } else {
                p.push_back(rnd.next(1, 1000));
            }
        }
        shuffle(p.begin(), p.end());
    } else if (mode == 4) {
        n = rnd.next(40, 120);
        m = rnd.next(1000, 20000000);
        int low = rnd.next(1, max(1, m / 20));
        int high = rnd.next(low, max(low, min(100000000, m)));
        for (int i = 0; i < n; ++i) p.push_back(rnd.next(low, high));
    } else {
        n = rnd.next(200, 1000);
        m = rnd.next(1, 200000000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) == 0) {
                p.push_back(rnd.next(1, 100000000));
            } else {
                p.push_back(rnd.next(1, 10000));
            }
        }
    }

    println(n, m);
    for (int value : p) println(value);

    return 0;
}
