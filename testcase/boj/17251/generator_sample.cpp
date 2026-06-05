#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(10, 40) * 2;
    } else {
        n = rnd.next(1, 10) * 2;
    }

    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) a[i] = value;
    } else if (mode == 1) {
        int start = rnd.next(1, 10000 - n + 1);
        int step = rnd.next(1, max(1, (10000 - start) / n));
        for (int i = 0; i < n; ++i) a[i] = min(10000, start + i * step);
    } else if (mode == 2) {
        int start = rnd.next(n, 10000);
        int step = rnd.next(1, max(1, (start - 1) / n));
        for (int i = 0; i < n; ++i) a[i] = max(1, start - i * step);
    } else if (mode == 3) {
        int low = rnd.next(1, 9000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, low);
        a[rnd.next(0, n / 2 - 1)] = rnd.next(low + 1, 10000);
    } else if (mode == 4) {
        int low = rnd.next(1, 9000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, low);
        a[rnd.next(n / 2, n - 1)] = rnd.next(low + 1, 10000);
    } else if (mode == 5) {
        int top = rnd.next(2, 10000);
        int low = rnd.next(1, top - 1);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, low);
        int left = rnd.next(0, n / 2 - 1);
        int right = rnd.next(n / 2, n - 1);
        a[left] = top;
        a[right] = top;
    } else {
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
