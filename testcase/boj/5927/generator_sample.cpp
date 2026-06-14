#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int boundedSquareSum(const vector<int>& a) {
    int total = 0;
    for (int x : a) total += x * x;
    return min(total, 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;
    int m;

    if (mode == 0) {
        n = 1;
        a = {rnd.next(1, 100)};
        int delta = rnd.next(-3, 3);
        int side = max(1, min(100, a[0] + delta));
        m = side * side;
    } else if (mode == 1) {
        n = 10;
        a.assign(n, rnd.next(80, 100));
        m = rnd.next(9500, 10000);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        a.resize(n);
        int base = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) a[i] = max(1, min(100, base + rnd.next(-2, 2)));
        int sum = boundedSquareSum(a);
        m = max(1, min(10000, sum + rnd.next(-20, 20)));
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 10);
        m = rnd.next(1, min(60, n * 100));
    } else if (mode == 4) {
        n = rnd.next(6, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0) ? rnd.next(1, 4) : rnd.next(70, 100);
        m = rnd.next(1, 10000);
    } else if (mode == 5) {
        n = rnd.next(1, 10);
        a.resize(n);
        vector<int> possibleSides;
        for (int x = 1; x <= 100 && x * x <= 10000; ++x) possibleSides.push_back(x);
        for (int i = 0; i < n; ++i) a[i] = rnd.any(possibleSides);
        m = rnd.any(a) * rnd.any(a);
        for (int i = 1; i < n && rnd.next(0, 1); ++i) {
            int side = rnd.next(1, 100);
            m = min(10000, m + side * side);
        }
    } else {
        n = rnd.next(1, 10);
        a.resize(n);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
        m = rnd.next(1, 10000);
    }

    shuffle(a.begin(), a.end());
    println(n, m);
    for (int x : a) println(x);

    return 0;
}
