#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    if (mode == 7) n = rnd.next(31, 120);

    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        long long base = rnd.next(1, 100);
        long long step = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) a.push_back(min(1000000000LL, base + step * i));
    } else if (mode == 1) {
        long long base = rnd.next(1, 100);
        long long step = rnd.next(0, 15);
        long long top = min(1000000000LL, base + step * (n - 1));
        for (int i = 0; i < n; ++i) a.push_back(max(1LL, top - step * i));
    } else if (mode == 2) {
        long long lo = rnd.next(1, 30);
        long long hi = rnd.next(lo, 200LL);
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? hi : lo);
    } else if (mode == 3) {
        long long value = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) a.push_back(value);
        int changes = rnd.next(1, min(n, 5));
        for (int i = 0; i < changes; ++i) a[rnd.next(n)] = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        long long low = rnd.next(1, 50);
        long long high = rnd.next(999999900, 1000000000);
        for (int i = 0; i < n; ++i) {
            if (i == 0) a.push_back(high);
            else if (i == 1) a.push_back(low);
            else if (i == n - 1) a.push_back(1000000000LL);
            else a.push_back(rnd.next(1, 1000000000));
        }
    } else if (mode == 5) {
        long long center = rnd.next(50, 500);
        for (int i = 0; i < n; ++i) {
            long long delta = rnd.next(0, 40);
            a.push_back(max(1LL, center + (i % 3 == 0 ? -delta : delta)));
        }
    } else {
        long long lo = rnd.next(1, 1000000000);
        long long hi = rnd.next(lo, 1000000000LL);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    println(n);
    println(a);
    return 0;
}
