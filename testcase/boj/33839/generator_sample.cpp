#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickValue(int mode) {
    if (mode == 0) return rnd.next(-10, 10);
    if (mode == 1) return rnd.any(vector<int>{-10000, -1000, -1, 0, 1, 1000, 10000});
    if (mode == 2) return rnd.next(0, 10000);
    if (mode == 3) return rnd.next(-10000, 0);
    if (rnd.next(2) == 0) return rnd.next(-10000, -9990);
    return rnd.next(9990, 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 4) {
        n = rnd.next(2, 20);
    } else {
        n = rnd.next(21, 80);
    }

    int k;
    int kMode = rnd.next(5);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = max(1, n / 2 + rnd.next(-1, 1));
    } else {
        k = rnd.next(1, n);
    }

    vector<int> a(n);
    if (mode == 1) {
        int value = pickValue(rnd.next(2));
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 10000);
    } else if (mode == 3) {
        int pivot = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            int magnitude = rnd.next(0, 10000);
            a[i] = (i < pivot ? -magnitude : magnitude);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = (i % 3 == 0 ? 0 : pickValue(1));
    } else {
        int valueMode = rnd.next(5);
        for (int i = 0; i < n; ++i) a[i] = pickValue(valueMode);
    }

    println(n, k);
    println(a);

    return 0;
}
