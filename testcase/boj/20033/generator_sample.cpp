#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 80);
    vector<long long> h(n);

    if (mode == 0) {
        long long value = rnd.next(1, 90);
        fill(h.begin(), h.end(), value);
    } else if (mode == 1) {
        long long start = rnd.next(1, 25);
        long long step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            h[i] = start + step * i;
        }
        if (rnd.next(0, 1)) {
            reverse(h.begin(), h.end());
        }
    } else if (mode == 2) {
        long long edge = rnd.next(1, 20);
        long long peak = rnd.next(edge, edge + 80);
        for (int i = 0; i < n; ++i) {
            int distance = min(i, n - 1 - i);
            h[i] = min(peak, edge + distance * rnd.next(1, 4));
        }
    } else if (mode == 3) {
        long long base = rnd.next(1, 15);
        long long spike = rnd.next(40, 200);
        for (int i = 0; i < n; ++i) {
            h[i] = (rnd.next(0, 99) < 25) ? spike + rnd.next(0, 50) : base + rnd.next(0, 8);
        }
    } else if (mode == 4) {
        int target = rnd.next(1, min(n, 30));
        for (int i = 0; i < n; ++i) {
            int block = (i / max(1, target / 2)) % 2;
            h[i] = block ? rnd.next(1, target) : rnd.next(target, target + 20);
        }
    } else if (mode == 5) {
        long long low = rnd.next(1, 6);
        long long high = rnd.next(100000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            h[i] = (rnd.next(0, 99) < 15) ? high : low + rnd.next(0, 20);
        }
    } else {
        int segmentCount = rnd.next(1, min(n, 8));
        int pos = 0;
        for (int segment = 0; segment < segmentCount; ++segment) {
            int remaining = n - pos;
            int length = (segment + 1 == segmentCount) ? remaining : rnd.next(1, remaining - (segmentCount - segment - 1));
            long long value = rnd.next(1, 100);
            for (int i = 0; i < length; ++i) {
                h[pos++] = value;
            }
        }
    }

    println(n);
    println(h);
    return 0;
}
