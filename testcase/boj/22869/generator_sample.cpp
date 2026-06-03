#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampHeight(int x) {
    return max(1, min(1000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 24);
    int k = rnd.next(1, 1000);
    vector<int> a(80);

    if (mode == 0) {
        k = rnd.next(1, 8);
        int base = rnd.next(1, 1000);
        fill(a.begin(), a.end(), base);
    } else if (mode == 1) {
        k = rnd.next(1, 12);
        a[0] = rnd.next(1, 1000);
        for (int i = 1; i < n; ++i) {
            int wiggle = max(0, k - 1);
            a[i] = clampHeight(a[i - 1] + rnd.next(-wiggle, wiggle));
        }
    } else if (mode == 2) {
        k = rnd.next(1, 20);
        int lo = rnd.next(1, 25);
        int hi = rnd.next(976, 1000);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? lo : hi);
    } else if (mode == 3) {
        k = rnd.next(1, 1000);
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(1, 1000);
        a[0] = lo;
        a[n - 1] = hi;
        for (int i = 1; i + 1 < n; ++i) a[i] = rnd.next(1, 1000);
    } else if (mode == 4) {
        n = rnd.next(18, 60);
        k = rnd.next(1, 1000);
        int span = rnd.next(0, 80);
        int low = rnd.next(1, 1000 - span);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(low, low + span);
    } else {
        n = rnd.next(2, 80);
        k = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 1000);
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    return 0;
}
