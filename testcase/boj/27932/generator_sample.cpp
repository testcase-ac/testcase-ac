#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 25);
    int k;
    if (rnd.next(0, 4) == 0) {
        k = rnd.any(vector<int>{0, n});
    } else {
        k = rnd.next(0, n);
    }

    vector<long long> h(n);

    if (mode == 0) {
        long long base = rnd.next(1LL, 1000000000LL);
        fill(h.begin(), h.end(), base);
    } else if (mode == 1) {
        long long base = rnd.next(1LL, 1000000000LL - n * 10LL);
        long long step = rnd.next(1LL, 10LL);
        for (int i = 0; i < n; ++i) h[i] = base + step * i;
        if (rnd.next(0, 1)) reverse(h.begin(), h.end());
    } else if (mode == 2) {
        long long low = rnd.next(1LL, 1000LL);
        long long high = rnd.next(1000000000LL - 1000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) h[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 3) {
        long long base = rnd.next(1000LL, 1000000000LL - 1000LL);
        long long gap = rnd.next(200LL, 1000LL);
        for (int i = 0; i < n; ++i) h[i] = base + rnd.next(-5LL, 5LL);
        int spikes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, n - 1);
            h[pos] = rnd.next(0, 1) ? base + gap : base - gap;
        }
    } else if (mode == 4) {
        long long cur = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            h[i] = cur;
            long long delta = rnd.next(-100000LL, 100000LL);
            cur = min(1000000000LL, max(1LL, cur + delta));
        }
    } else {
        for (int i = 0; i < n; ++i) h[i] = rnd.next(1LL, 1000000000LL);
    }

    println(n, k);
    println(h);

    return 0;
}
