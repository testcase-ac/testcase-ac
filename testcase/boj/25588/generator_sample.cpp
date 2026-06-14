#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int nextStepValue(int value) {
    if (value == 1) return 2;
    if (value == 9) return 8;
    return value + (rnd.next(0, 1) == 0 ? -1 : 1);
}

static void appendStair(vector<int>& a, int len) {
    int value = rnd.next(1, 9);
    for (int i = 0; i < len; ++i) {
        a.push_back(value);
        value = nextStepValue(value);
    }
}

static void appendNoise(vector<int>& a, int len, int lo = 1, int hi = 9) {
    for (int i = 0; i < len; ++i) a.push_back(rnd.next(lo, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 45);
    vector<int> a;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(3, 12);
        k = rnd.next(1, n);
        appendNoise(a, n);
    } else if (mode == 1) {
        n = rnd.next(3, 35);
        appendStair(a, n);
        k = rnd.any(vector<int>{1, min(3, n), rnd.next(1, n), n});
    } else if (mode == 2) {
        n = rnd.next(8, 45);
        int firstLen = rnd.next(3, n - 3);
        appendStair(a, firstLen);
        appendNoise(a, 1);
        appendStair(a, n - firstLen - 1);
        k = rnd.next(max(1, firstLen - 2), min(n, firstLen + 2));
    } else if (mode == 3) {
        n = rnd.next(3, 40);
        int x = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) a.push_back((i + x) % 2 == 0 ? 1 : 9);
        k = rnd.any(vector<int>{1, 2, 3, rnd.next(1, n)});
    } else if (mode == 4) {
        n = rnd.next(12, 45);
        while ((int)a.size() < n) {
            int remaining = n - (int)a.size();
            int len = rnd.next(1, min(remaining, 8));
            if (rnd.next(0, 1) == 0) appendStair(a, len);
            else appendNoise(a, len);
        }
        k = rnd.next(1, n);
    } else {
        n = rnd.next(3, 100);
        int lo = rnd.next(1, 7);
        int hi = rnd.next(lo, 9);
        appendNoise(a, n, lo, hi);
        k = rnd.next(max(1, n - 5), n);
    }

    println(n, k);
    println(a);
    return 0;
}
