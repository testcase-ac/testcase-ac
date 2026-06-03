#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_H = 1000000000LL;

vector<long long> increasingRun(int n, long long start, int stepLo, int stepHi) {
    vector<long long> a(n);
    long long cur = start;
    for (int i = 0; i < n; ++i) {
        a[i] = cur;
        if (i + 1 < n) cur += rnd.next(stepLo, stepHi);
    }
    return a;
}

vector<long long> decreasingRun(int n, long long start, int stepLo, int stepHi) {
    vector<long long> a(n);
    long long cur = start;
    for (int i = 0; i < n; ++i) {
        a[i] = cur;
        if (i + 1 < n) cur -= rnd.next(stepLo, stepHi);
    }
    return a;
}

vector<long long> boundedRandom(int n, long long lo, long long hi) {
    vector<long long> a(n);
    for (long long &x : a) x = rnd.next(lo, hi);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 8);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 7);
        int n = rnd.next(1, 24);
        vector<long long> a;

        if (mode == 0) {
            n = rnd.next(1, 24);
            a = increasingRun(n, rnd.next(1LL, 50LL), 1, 12);
        } else if (mode == 1) {
            n = rnd.next(1, 24);
            a = decreasingRun(n, rnd.next(200LL, 500LL), 1, 12);
        } else if (mode == 2) {
            n = rnd.next(2, 24);
            a = boundedRandom(n, 1, rnd.next(2, 20));
        } else if (mode == 3) {
            int left = rnd.next(1, 8);
            int mid = rnd.next(1, 6);
            int right = rnd.next(1, 8);
            n = left + mid + right;
            vector<long long> l = increasingRun(left, rnd.next(1LL, 30LL), 1, 6);
            vector<long long> r = increasingRun(right, l.back() + rnd.next(1, 5), 1, 6);
            vector<long long> noise = boundedRandom(mid, 1, 60);
            a = l;
            a.insert(a.end(), noise.begin(), noise.end());
            a.insert(a.end(), r.begin(), r.end());
        } else if (mode == 4) {
            int left = rnd.next(1, 8);
            int mid = rnd.next(1, 6);
            int right = rnd.next(1, 8);
            n = left + mid + right;
            vector<long long> l = increasingRun(left, rnd.next(100LL, 200LL), 1, 8);
            vector<long long> r = increasingRun(right, rnd.next(1LL, 80LL), 1, 8);
            vector<long long> dip = boundedRandom(mid, 1, 25);
            a = l;
            a.insert(a.end(), dip.begin(), dip.end());
            a.insert(a.end(), r.begin(), r.end());
        } else if (mode == 5) {
            n = rnd.next(3, 24);
            long long base = rnd.next(1LL, 100LL);
            for (int i = 0; i < n; ++i) {
                int block = i / rnd.next(2, 4);
                a.push_back(min(MAX_H, base + block + rnd.next(0, 1)));
            }
        } else if (mode == 6) {
            n = rnd.next(3, 24);
            long long cur = rnd.next(1LL, 80LL);
            for (int i = 0; i < n; ++i) {
                a.push_back(cur);
                if (rnd.next(0, 2) == 0) cur = max(1LL, cur - rnd.next(1, 10));
                else cur = min(MAX_H, cur + rnd.next(1, 10));
            }
        } else {
            n = rnd.next(2, 24);
            a = boundedRandom(n, MAX_H - 1000, MAX_H);
        }

        println(n);
        println(a);
    }

    return 0;
}
