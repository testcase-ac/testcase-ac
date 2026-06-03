#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(mode <= 1 ? 2 : 3, 30);
    if (rnd.next(0, 9) == 0) n = rnd.next(31, 120);

    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = n;
    } else {
        k = rnd.next(2, n - 1);
    }

    int lo = rnd.next(1, 70);
    int hi = rnd.next(lo, 100);
    vector<int> a(n);

    if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 30);

        int left = rnd.next(1, k - 1);
        int right = k - left;
        for (int i = 0; i < left; ++i) a[i] = rnd.next(80, 100);
        for (int i = 0; i < right; ++i) a[n - right + i] = rnd.next(80, 100);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 40);

        int start = rnd.next(0, n - k);
        for (int i = 0; i < k; ++i) a[start + i] = rnd.next(70, 100);
    } else if (mode == 4) {
        int value = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) a[i] = value;
    } else {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    println(n, k);
    println(a);

    return 0;
}
