#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedValue(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(100000, center + radius);
    return rnd.next(lo, hi);
}

vector<int> makeValues(int n, int mode) {
    vector<int> v;
    v.reserve(n);

    if (mode == 0) {
        int base = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) v.push_back(base);
    } else if (mode == 1) {
        int base = rnd.next(2, 99999);
        int radius = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) v.push_back(boundedValue(base, radius));
    } else if (mode == 2) {
        vector<int> pool = {1, 2, 3, 99998, 99999, 100000};
        for (int i = 0; i < n; ++i) v.push_back(rnd.any(pool));
    } else {
        int lo = rnd.next(1, 90000);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 10000)));
        for (int i = 0; i < n; ++i) v.push_back(rnd.next(lo, hi));
    }

    if (rnd.next(2)) shuffle(v.begin(), v.end());
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n = sizeMode == 0 ? 1 : rnd.next(2, sizeMode <= 2 ? 12 : 40);
    int m = sizeMode == 1 ? 1 : rnd.next(2, sizeMode <= 2 ? 12 : 40);

    int mode = rnd.next(6);
    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        int shared = rnd.next(1, 100000);
        a.assign(n, shared);
        b.assign(m, shared);
    } else if (mode == 1) {
        a = makeValues(n, 1);
        int pivot = rnd.next(2, 99999);
        for (int& x : a) x = rnd.next(1, pivot);
        for (int i = 0; i < m; ++i) b.push_back(rnd.next(pivot, 100000));
    } else if (mode == 2) {
        int pivot = rnd.next(2, 99999);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(pivot, 100000));
        for (int i = 0; i < m; ++i) b.push_back(rnd.next(1, pivot));
    } else if (mode == 3) {
        a = makeValues(n, 2);
        b = makeValues(m, 2);
    } else if (mode == 4) {
        int center = rnd.next(1, 100000);
        int radius = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) a.push_back(boundedValue(center, radius));
        for (int i = 0; i < m; ++i) b.push_back(boundedValue(center, radius));
    } else {
        a = makeValues(n, 3);
        b = makeValues(m, 3);
    }

    if (rnd.next(2)) sort(a.begin(), a.end());
    if (rnd.next(2)) sort(b.begin(), b.end());

    println(n, m);
    println(a);
    println(b);
    return 0;
}
