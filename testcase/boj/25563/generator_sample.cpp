#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000;

int randomSubmask(int mask) {
    int x = 0;
    for (int bit = 0; bit < 20; ++bit) {
        int b = 1 << bit;
        if ((mask & b) && rnd.next(2)) x |= b;
    }
    return x;
}

int randomSupermask(int mask) {
    int x = mask;
    for (int bit = 0; bit < 20; ++bit) {
        int b = 1 << bit;
        if (!(mask & b) && rnd.next(2)) {
            int y = x | b;
            if (y <= MAX_VALUE) x = y;
        }
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 60);
    int k = rnd.next(0, MAX_VALUE);
    vector<int> a;

    if (mode == 0) {
        int hi = rnd.next(0, min(MAX_VALUE, 127));
        k = rnd.next(0, hi);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, hi));
    } else if (mode == 1) {
        k = rnd.any(vector<int>{0, 1, 2, 3, 7, 15, 255, 1023, MAX_VALUE});
        int distinct = rnd.next(1, min(8, n));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(0, MAX_VALUE));
        pool.push_back(k);
        while ((int)a.size() < n) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        k = rnd.next(0, MAX_VALUE);
        for (int i = 0; i < n; ++i) a.push_back(randomSubmask(k));
    } else if (mode == 3) {
        k = rnd.next(0, MAX_VALUE);
        for (int i = 0; i < n; ++i) a.push_back(randomSupermask(k));
    } else if (mode == 4) {
        n = rnd.next(2, 50);
        k = rnd.next(0, MAX_VALUE);
        for (int i = 0; i + 1 < n; i += 2) {
            int x = rnd.next(0, MAX_VALUE);
            int y = x ^ k;
            if (y > MAX_VALUE) y = rnd.next(0, MAX_VALUE);
            a.push_back(x);
            a.push_back(y);
        }
        if ((int)a.size() < n) a.push_back(rnd.next(0, MAX_VALUE));
    } else {
        vector<int> pool = {0, 1, 2, 3, 7, 15, 31, 255, 1023, 999999, MAX_VALUE};
        k = rnd.any(pool);
        while ((int)a.size() < n) {
            int x = rnd.any(pool);
            if (rnd.next(3) == 0) x = rnd.next(max(0, x - 3), min(MAX_VALUE, x + 3));
            a.push_back(x);
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size(), k);
    println(a);
    return 0;
}
