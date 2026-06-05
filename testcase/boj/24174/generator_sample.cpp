#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(5, 28);
    if (mode == 7) {
        n = rnd.next(35, 80);
    }

    int k;
    if (mode <= 2) {
        k = rnd.next(1, min(12, n * 3));
    } else if (mode <= 5) {
        k = rnd.next(1, n * 8);
    } else {
        k = rnd.next(n * 8 + 1, n * 30);
    }

    vector<int> a(n);
    int start = rnd.next(1, 1000000000 - 3 * n - 100);
    int step = rnd.next(1, 7);
    for (int i = 0; i < n; ++i) {
        a[i] = start + i * step;
    }

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        rotate(a.begin(), a.begin() + rnd.next(1, n - 1), a.end());
    } else if (mode == 3) {
        for (int i = 0; i < n / 2; ++i) {
            swap(a[i], a[n - 1 - i]);
        }
        int swaps = rnd.next(1, n);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    } else if (mode == 4) {
        vector<int> odds, evens;
        for (int i = 0; i < n; ++i) {
            (i % 2 == 0 ? evens : odds).push_back(a[i]);
        }
        a.clear();
        a.insert(a.end(), odds.begin(), odds.end());
        a.insert(a.end(), evens.begin(), evens.end());
    } else if (mode == 5) {
        sort(a.begin(), a.end());
        int block = rnd.next(2, min(7, n));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            shuffle(a.begin() + l, a.begin() + r);
        }
    } else if (mode == 6) {
        sort(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n, k);
    println(a);

    return 0;
}
