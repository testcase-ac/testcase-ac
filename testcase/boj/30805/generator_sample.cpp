#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> randomSeq(int n, int lo, int hi) {
    vector<int> v(n);
    for (int &x : v) x = rnd.next(lo, hi);
    return v;
}

static void appendRandom(vector<int> &v, int count, int lo, int hi) {
    for (int i = 0; i < count; ++i) v.push_back(rnd.next(lo, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a, b;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(1, 20);
        int m = rnd.next(1, 20);
        a = randomSeq(n, 1, 45);
        b = randomSeq(m, 56, 100);
    } else if (mode == 1) {
        int n = rnd.next(1, 30);
        a = randomSeq(n, 1, 100);
        b = a;
    } else if (mode == 2) {
        int common = rnd.next(1, 8);
        vector<int> core;
        for (int i = 0; i < common; ++i) core.push_back(rnd.next(70, 100));
        sort(core.rbegin(), core.rend());

        appendRandom(a, rnd.next(0, 8), 1, 69);
        appendRandom(b, rnd.next(0, 8), 1, 69);
        for (int x : core) {
            appendRandom(a, rnd.next(0, 3), 1, 69);
            appendRandom(b, rnd.next(0, 3), 1, 69);
            a.push_back(x);
            b.push_back(x);
        }
        appendRandom(a, rnd.next(0, 8), 1, 69);
        appendRandom(b, rnd.next(0, 8), 1, 69);
    } else if (mode == 3) {
        int n = rnd.next(8, 35);
        int m = rnd.next(8, 35);
        a = randomSeq(n, 1, 70);
        b = randomSeq(m, 1, 70);
        int shared = rnd.next(71, 100);
        a[rnd.next(n)] = shared;
        b[rnd.next(m)] = shared;
        for (int i = 0; i < rnd.next(1, 5); ++i) a[rnd.next(n)] = rnd.next(shared, 100);
        for (int i = 0; i < rnd.next(1, 5); ++i) b[rnd.next(m)] = rnd.next(shared, 100);
    } else if (mode == 4) {
        int n = rnd.next(10, 45);
        int m = rnd.next(10, 45);
        int pivot = rnd.next(40, 80);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next() < 0.55 ? pivot : rnd.next(1, 100));
        for (int i = 0; i < m; ++i) b.push_back(rnd.next() < 0.55 ? pivot : rnd.next(1, 100));
    } else {
        int n = rnd.next(1, 60);
        int m = rnd.next(1, 60);
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 100);
        a = randomSeq(n, lo, hi);
        b = randomSeq(m, lo, hi);
    }

    println((int)a.size());
    println(a);
    println((int)b.size());
    println(b);

    return 0;
}
