#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(13, 20);
    } else if (mode == 4) {
        n = rnd.next(21, 40);
    } else {
        n = rnd.next(80, 100);
    }

    int m = n * (n - 1) / 2;
    vector<long long> costs;
    costs.reserve(m);

    int pattern = rnd.next(0, 5);
    if (pattern == 0) {
        long long lo = rnd.next(1, 30);
        long long hi = lo + rnd.next(0, 70);
        for (int i = 0; i < m; ++i) costs.push_back(rnd.next(lo, hi));
    } else if (pattern == 1) {
        vector<long long> pool;
        int poolSize = rnd.next(1, min(6, m));
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, 100));
        for (int i = 0; i < m; ++i) costs.push_back(rnd.any(pool));
    } else if (pattern == 2) {
        long long base = rnd.next(1, 1000);
        long long step = rnd.next(1, 20);
        for (int i = 0; i < m; ++i) costs.push_back(base + step * i);
    } else if (pattern == 3) {
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 9) == 0) {
                costs.push_back(rnd.next(1000000000LL, 2000000000LL));
            } else {
                costs.push_back(rnd.next(1, 1000));
            }
        }
    } else if (pattern == 4) {
        long long a = rnd.next(1, 20);
        long long b = rnd.next(1000000000LL, 2000000000LL);
        for (int i = 0; i < m; ++i) costs.push_back(rnd.next(0, 1) == 0 ? a : b);
    } else {
        for (int i = 0; i < m; ++i) costs.push_back(rnd.next(1LL, 2000000000LL));
    }

    if (rnd.next(0, 2) == 0) {
        shuffle(costs.begin(), costs.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(costs.begin(), costs.end());
    } else {
        sort(costs.rbegin(), costs.rend());
    }

    println(n);
    println(costs);

    return 0;
}
