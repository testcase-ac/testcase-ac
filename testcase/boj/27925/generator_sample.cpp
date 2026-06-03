#include "testlib.h"

#include <vector>

using namespace std;

int circularStep(int x, int delta) {
    x = (x + delta) % 10;
    if (x < 0) x += 10;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    vector<int> t;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int value = rnd.next(0, 9);
        t.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int a = rnd.next(0, 9);
        int b = circularStep(a, rnd.any(vector<int>{1, 4, 5, 6, 9}));
        for (int i = 0; i < n; ++i) t.push_back(i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        n = rnd.next(6, 45);
        int cur = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            t.push_back(cur);
            cur = circularStep(cur, rnd.any(vector<int>{-2, -1, 1, 2}));
        }
    } else if (mode == 3) {
        n = rnd.next(8, 60);
        vector<int> pool;
        int base = rnd.next(0, 9);
        pool.push_back(base);
        pool.push_back(circularStep(base, rnd.next(1, 3)));
        pool.push_back(circularStep(base, rnd.next(4, 6)));
        for (int i = 0; i < n; ++i) t.push_back(rnd.any(pool));
    } else if (mode == 4) {
        n = rnd.next(10, 70);
        int cur = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(2, 5) == 0) cur = rnd.next(0, 9);
            t.push_back(cur);
        }
    } else if (mode == 5) {
        n = rnd.next(12, 80);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(0, 9));
    } else if (mode == 6) {
        n = rnd.next(10, 80);
        int cur = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            t.push_back(cur);
            cur = circularStep(cur, rnd.next(3, 7));
        }
    } else {
        n = rnd.next(80, 180);
        for (int i = 0; i < n; ++i) {
            int block = i / rnd.next(3, 9);
            t.push_back((block + rnd.next(0, 2) * 5 + rnd.next(0, 1)) % 10);
        }
    }

    println(n);
    println(t);
    return 0;
}
