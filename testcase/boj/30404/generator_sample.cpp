#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeDense(int n, int lo, int hi) {
    vector<int> pool;
    for (int x = lo; x <= hi; ++x) pool.push_back(x);
    shuffle(pool.begin(), pool.end());
    pool.resize(n);
    sort(pool.begin(), pool.end());
    return pool;
}

static vector<int> makeStepped(int n, int start, int minGap, int maxGap) {
    vector<int> x;
    x.push_back(start);
    for (int i = 1; i < n; ++i) {
        x.push_back(x.back() + rnd.next(minGap, maxGap));
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k;
    vector<int> x;

    if (mode == 0) {
        n = rnd.next(1, 6);
        k = rnd.next(0, 3);
        x = makeDense(n, 1, 10);
    } else if (mode == 1) {
        k = rnd.next(0, 8);
        int gap = k + 1;
        int start = rnd.next(1, 20);
        x = makeStepped(n, start, gap, gap);
    } else if (mode == 2) {
        k = rnd.next(1, 20);
        int start = rnd.next(1, 40);
        x = makeStepped(n, start, 1, k + 2);
    } else if (mode == 3) {
        n = rnd.next(15, 60);
        k = rnd.next(100000, 1000000);
        int hi = rnd.next(100000, 1000000);
        x = makeDense(n, 1, hi);
    } else if (mode == 4) {
        n = rnd.next(2, 35);
        k = rnd.any(vector<int>{0, 1, 999999, 1000000});
        x = makeDense(n, 1000000 - n + 1, 1000000);
    } else {
        k = rnd.next(1, 50);
        int cur = rnd.next(1, 30);
        x.push_back(cur);
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 2) == 0) cur += rnd.next(1, k);
            else cur += rnd.next(k + 1, k + 20);
            x.push_back(cur);
        }
    }

    while (!x.empty() && x.back() > 1000000) {
        x.pop_back();
    }
    n = (int)x.size();

    println(n, k);
    println(x);
    return 0;
}
