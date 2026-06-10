#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 7) {
        n = 100;
    } else if (mode == 6) {
        n = rnd.next(50, 100);
    } else {
        n = rnd.next(1, 30);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        // Already sorted, including the zero-operation case.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 1);
            int other = min(n - 1, pos + rnd.next(0, 2));
            swap(a[pos], a[other]);
        }
    } else if (mode == 3) {
        int left = rnd.next(0, n - 1);
        int right = rnd.next(left, n - 1);
        reverse(a.begin() + left, a.begin() + right + 1);
    } else if (mode == 4) {
        int block = rnd.next(1, min(n, 10));
        for (int left = 0; left < n; left += block) {
            int right = min(n, left + block);
            if (rnd.next(0, 1)) {
                reverse(a.begin() + left, a.begin() + right);
            }
        }
    } else if (mode == 5) {
        if (n > 1) {
            rotate(a.begin(), a.begin() + rnd.next(1, n - 1), a.end());
        }
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
