#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int N;

    int type = rnd.next(0, 8);

    if (type == 0) {
        // Tiny array
        N = rnd.next(1, 3);
        a.assign(N, 0);
        for (int i = 0; i < N; ++i)
            a[i] = rnd.next(0, 10);
    } else if (type == 1) {
        // All equal
        N = rnd.next(3, 15);
        vector<int> candidates = {0, 1, 2, 3, 5, 10, 1000000};
        int v = rnd.any(candidates);
        a.assign(N, v);
    } else if (type == 2) {
        // Single peak
        N = rnd.next(5, 20);
        a.assign(N, 0);
        int base = rnd.next(1, 9);
        for (int i = 0; i < N; ++i)
            a[i] = base + rnd.next(0, 2); // [base, base+2]
        int k = rnd.next(0, N - 1);
        int big;
        if (rnd.next(0, 1) == 0) big = rnd.next(20, 100);
        else big = 1000000;
        a[k] = big;
    } else if (type == 3) {
        // Single valley
        N = rnd.next(5, 20);
        a.assign(N, 0);
        int high;
        if (rnd.next(0, 1) == 0) high = rnd.next(10, 100);
        else high = 1000000;
        for (int i = 0; i < N; ++i)
            a[i] = high - rnd.next(0, 2); // near high, stay non-negative
        int k = rnd.next(0, N - 1);
        int low = rnd.next(0, 1); // 0 or 1
        a[k] = low;
        if (N >= 3 && rnd.next(0, 1) == 1) {
            if (k > 0) a[k - 1] = low;
            if (k + 1 < N) a[k + 1] = low;
        }
    } else if (type == 4) {
        // Random small with at least one zero
        N = rnd.next(5, 30);
        a.assign(N, 0);
        for (int i = 0; i < N; ++i)
            a[i] = rnd.next(0, 9);
        int k = rnd.next(0, N - 1);
        a[k] = 0;
    } else if (type == 5) {
        // Increasing sequence
        N = rnd.next(5, 20);
        a.assign(N, 0);
        int start = rnd.next(0, 3);
        int step = rnd.next(1, 5);
        for (int i = 0; i < N; ++i) {
            long long val = (long long)start + 1LL * i * step;
            if (val > 1000000) val = 1000000;
            a[i] = (int)val;
        }
    } else if (type == 6) {
        // Decreasing sequence
        N = rnd.next(5, 20);
        a.assign(N, 0);
        int step = rnd.next(1, 5);
        long long minStart = 1LL * step * (N - 1);
        long long start = min(1000000LL, minStart + rnd.next(0, 3));
        for (int i = 0; i < N; ++i) {
            long long val = start - 1LL * i * step;
            if (val < 0) val = 0;
            a[i] = (int)val;
        }
    } else if (type == 7) {
        // Zigzag high/low
        N = rnd.next(6, 20);
        a.assign(N, 0);
        int low = rnd.next(0, 5);
        int high;
        if (rnd.next(0, 1) == 0) high = rnd.next(10, 50);
        else high = 1000000;
        for (int i = 0; i < N; ++i)
            a[i] = (i % 2 == 0 ? high : low);
    } else {
        // Mixed equal blocks with guaranteed zero and big
        N = rnd.next(5, 25);
        int blocks = rnd.next(2, min(5, N));
        vector<int> lens(blocks);
        int remaining = N;
        for (int b = 0; b < blocks; ++b) {
            int remBlocks = blocks - b;
            int maxLen = remaining - (remBlocks - 1);
            int len = (b == blocks - 1 ? remaining : rnd.next(1, maxLen));
            lens[b] = len;
            remaining -= len;
        }
        a.clear();
        a.reserve(N);
        bool hasZero = false, hasBig = false;
        for (int b = 0; b < blocks; ++b) {
            int kind = rnd.next(0, 2);
            int val;
            if (kind == 0) val = rnd.next(0, 9);
            else if (kind == 1) val = rnd.next(10, 100);
            else val = 1000000;
            if (val == 0) hasZero = true;
            if (val >= 500000) hasBig = true;
            for (int i = 0; i < lens[b]; ++i)
                a.push_back(val);
        }
        N = (int)a.size();
        if (!hasZero) {
            int pos = rnd.next(0, N - 1);
            a[pos] = 0;
        }
        if (!hasBig) {
            int pos = rnd.next(0, N - 1);
            a[pos] = 1000000;
        }
    }

    N = (int)a.size();
    println(N);
    println(a);

    return 0;
}
