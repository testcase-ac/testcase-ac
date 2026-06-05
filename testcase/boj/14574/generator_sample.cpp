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
    } else if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(3, 14);
    }

    vector<long long> p;
    vector<long long> c(n);

    if (mode == 1) {
        long long start = rnd.next(0, 1000);
        long long gap = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) p.push_back(start + gap * i);
    } else if (mode == 2) {
        long long start = rnd.next(0, 1000000000 - n + 1);
        for (int i = 0; i < n; ++i) p.push_back(start + i);
    } else if (mode == 3) {
        long long step = 1000000000LL / (n + 1);
        for (int i = 0; i < n; ++i) {
            long long jitter = rnd.next(0LL, max(0LL, step / 3));
            p.push_back(min(1000000000LL, step * (i + 1) + jitter));
        }
    } else if (mode == 4) {
        p.push_back(0);
        p.push_back(1000000000LL);
        while ((int)p.size() < n) {
            long long value = rnd.next(1LL, 999999999LL);
            if (find(p.begin(), p.end(), value) == p.end()) p.push_back(value);
        }
    } else {
        while ((int)p.size() < n) {
            long long value = rnd.next(0LL, 1000000000LL);
            if (find(p.begin(), p.end(), value) == p.end()) p.push_back(value);
        }
    }

    sort(p.begin(), p.end());

    if (mode == 0) {
        c[0] = rnd.next(0LL, 3LL);
        c[1] = rnd.next(999999990LL, 1000000000LL);
    } else if (mode == 1) {
        long long base = rnd.next(0LL, 30LL);
        for (int i = 0; i < n; ++i) c[i] = base + rnd.next(0LL, 20LL);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? 1000000000LL : rnd.next(0LL, 10LL));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0LL, 1000000000LL);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) c[i] = (long long)i * 1000000000LL / max(1, n - 1);
    } else {
        long long hi = rnd.next(1000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0LL, hi);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    println(n);
    for (int idx : order) println(p[idx], c[idx]);

    return 0;
}
