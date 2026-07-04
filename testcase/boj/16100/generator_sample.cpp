#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int boundedHeight(long long value) {
    return (int)max(1LL, min(100000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> h;

    if (mode == 0) {
        h.push_back(rnd.next(1, 100000));
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int start = rnd.next(1, 40);
        int step = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) {
            h.push_back(boundedHeight(start + 1LL * i * step + rnd.next(0, 3)));
        }
        if (rnd.next(0, 1)) reverse(h.begin(), h.end());
    } else if (mode == 2) {
        int n = rnd.next(3, 15);
        int peak = rnd.next(1, n);
        int cur = rnd.next(1, 20);
        for (int i = 1; i <= n; ++i) {
            if (i <= peak) {
                cur += rnd.next(0, 12);
            } else {
                cur -= rnd.next(0, 12);
            }
            h.push_back(boundedHeight(cur));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 16);
        int low = rnd.next(1, 25);
        int high = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            int wobble = rnd.next(0, 20);
            h.push_back(i % 2 == 0 ? boundedHeight(high - wobble) : boundedHeight(low + wobble));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 18);
        int base = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 25);
            h.push_back(boundedHeight(1LL * base * multiplier + rnd.next(0, base - 1)));
        }
    } else if (mode == 5) {
        int n = rnd.next(8, 30);
        int maxHeight = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            h.push_back(rnd.next(1, maxHeight));
        }
    } else {
        int n = rnd.next(40, 120);
        int pivot = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - pivot) + 1;
            long long value = 100000LL / distance + rnd.next(0, 200);
            h.push_back(boundedHeight(value));
        }
        shuffle(h.begin(), h.end());
    }

    println((int)h.size());
    println(h);
    return 0;
}
