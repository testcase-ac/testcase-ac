#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    if (rnd.next(0, 9) == 0) n = rnd.next(41, 200);

    vector<int> h(n);
    int low = rnd.next(1, 30);
    int high = rnd.next(low, min(1000000, low + rnd.next(0, 200)));

    if (mode == 0) {
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            cur = min(1000000, cur + rnd.next(0, 30));
            h[i] = cur;
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            cur = max(1, cur - rnd.next(0, 30));
            h[i] = cur;
        }
    } else if (mode == 2) {
        int a = rnd.next(1, 20);
        int b = rnd.next(a, min(1000000, a + rnd.next(0, 1000)));
        int c = rnd.next(b, 1000000);
        for (int i = 0; i < n; ++i) h[i] = rnd.any(vector<int>{a, b, c});
    } else if (mode == 3) {
        int left = rnd.next(1, 1000000);
        int bottom = rnd.next(1, left);
        int right = rnd.next(bottom, 1000000);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            int base = (i < n / 2 ? left : right);
            h[i] = max(bottom, base - dist * rnd.next(0, 20));
        }
    } else if (mode == 4) {
        int small = rnd.next(1, 5);
        int large = rnd.next(500000, 1000000);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0) ? small + rnd.next(0, 3) : large - rnd.next(0, 1000);
        }
    } else if (mode == 5) {
        int block = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) {
                low = rnd.next(1, 1000);
                high = rnd.next(low, 1000000);
            }
            h[i] = rnd.next(low, high);
        }
    } else {
        for (int i = 0; i < n; ++i) h[i] = rnd.next(low, high);
    }

    println(n);
    for (int value : h) println(value);

    return 0;
}
