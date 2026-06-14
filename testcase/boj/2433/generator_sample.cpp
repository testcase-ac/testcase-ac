#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int c;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        c = rnd.next(0, 3);
        int base = rnd.next(0, 100);
        a.assign(n, base + rnd.next(0, c));
    } else if (mode == 1) {
        n = rnd.next(8, 30);
        m = rnd.next(2, min(10, n));
        c = rnd.next(0, 5);
        int base = rnd.next(0, 200);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = base + rnd.next(0, c);
        }
        int spikeCount = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < spikeCount; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] = base + c + rnd.next(1, 20);
        }
    } else if (mode == 2) {
        n = rnd.next(10, 40);
        m = rnd.next(2, min(12, n));
        c = rnd.next(0, 10);
        int low = rnd.next(0, 500);
        int high = low + c + rnd.next(1, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? low : high);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        m = rnd.next(2, min(12, n));
        c = rnd.next(0, 10000);
        int start = rnd.next(0, 1000000 - n);
        int step = rnd.next(0, 3);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i * step;
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(1, 20);
        m = rnd.next(n + 1, min(10000, n + 40));
        c = rnd.next(0, 10000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1000000);
        }
    } else {
        n = rnd.next(20, 80);
        m = rnd.next(1, min(15, n));
        c = rnd.next(0, 10000);
        int lo = rnd.next(0, 999000);
        int width = rnd.next(0, min(20000, 1000000 - lo));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = lo + rnd.next(0, width);
        }
    }

    println(n, m, c);
    println(a);

    return 0;
}
