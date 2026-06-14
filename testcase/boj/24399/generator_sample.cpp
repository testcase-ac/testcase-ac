#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 55) {
        n = rnd.next(5, 20);
    } else if (sizeMode < 90) {
        n = rnd.next(21, 120);
    } else {
        n = rnd.next(121, 400);
    }

    int qMode = rnd.next(100);
    int q;
    if (qMode < 20) {
        q = 1;
    } else if (qMode < 40) {
        q = n;
    } else if (qMode < 60) {
        q = (n + 1) / 2;
    } else {
        q = rnd.next(1, n);
    }

    int kMode = rnd.next(100);
    int k;
    if (kMode < 25) {
        k = rnd.next(1, min(20, n * n));
    } else if (kMode < 50) {
        k = rnd.next(max(1, n / 2), min(100000000, n * 20));
    } else if (kMode < 75) {
        k = rnd.next(1, 100000000);
    } else {
        k = 100000000;
    }

    vector<int> a(n);
    int shape = rnd.next(6);
    if (shape == 0) {
        iota(a.begin(), a.end(), 1);
    } else if (shape == 1) {
        iota(a.begin(), a.end(), 1);
        reverse(a.begin(), a.end());
    } else if (shape == 2) {
        iota(a.begin(), a.end(), 1);
        for (int i = 0; i < max(1, n / 8); ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    } else if (shape == 3) {
        iota(a.begin(), a.end(), 1);
        rotate(a.begin(), a.begin() + rnd.next(n), a.end());
    } else if (shape == 4) {
        iota(a.begin(), a.end(), 1);
        shuffle(a.begin(), a.end());
    } else {
        vector<int> candidates;
        int step = rnd.next(1, 20);
        int base = rnd.next(1, 1000000000 - (2 * n - 1) * step);
        for (int i = 0; i < 2 * n; ++i) {
            candidates.push_back(base + i * step);
        }
        shuffle(candidates.begin(), candidates.end());
        a.assign(candidates.begin(), candidates.begin() + n);
    }

    if (rnd.next(100) < 35) {
        for (int& x : a) {
            x = 1000000001 - x;
        }
    }

    println(n, q, k);
    println(a);

    return 0;
}
