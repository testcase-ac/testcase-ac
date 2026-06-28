#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int p;

    if (mode == 0) {
        n = rnd.next(1, 4);
        p = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(5, 15);
        p = rnd.next(1, min(n, 3));
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        p = n;
    } else if (mode == 3) {
        n = rnd.next(8, 25);
        p = rnd.next(max(1, n / 3), n);
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        p = rnd.next(2, min(n, 8));
    } else {
        n = rnd.next(6, 24);
        p = rnd.next(1, n);
    }

    vector<long long> c(n);
    int costMode = rnd.next(0, 6);
    if (costMode == 0) {
        long long base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) c[i] = base + i * rnd.next(0, 4);
    } else if (costMode == 1) {
        long long base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) c[i] = base + (n - 1 - i) * rnd.next(0, 4);
    } else if (costMode == 2) {
        long long low = rnd.next(1, 10);
        long long high = rnd.next(50, 200);
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? low + rnd.next(0, 5) : high + rnd.next(0, 50));
    } else if (costMode == 3) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            c[i] = 1 + 1LL * abs(i - center) * rnd.next(1, 9) + rnd.next(0, 3);
        }
    } else if (costMode == 4) {
        long long a = rnd.next(1, 100);
        long long b = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0, 1) ? a : b;
    } else if (costMode == 5) {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, 1000000000);
    } else {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, 100);
        c[rnd.next(0, n - 1)] = 1;
        c[rnd.next(0, n - 1)] = 1000000000LL;
    }

    println(n, p);
    println(c);
    return 0;
}
