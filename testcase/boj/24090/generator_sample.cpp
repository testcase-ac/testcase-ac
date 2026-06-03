#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long countSwaps(vector<int> a, int p, int r) {
    if (p >= r) return 0;

    int pivot = a[r];
    int i = p - 1;
    long long swaps = 0;
    for (int j = p; j < r; ++j) {
        if (a[j] <= pivot) {
            ++i;
            swap(a[i], a[j]);
            ++swaps;
        }
    }
    if (i + 1 != r) {
        swap(a[i + 1], a[r]);
        ++swaps;
    }

    return swaps + countSwaps(a, p, i) + countSwaps(a, i + 2, r);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, mode == 5 ? 60 : 25);

    vector<int> a(n);
    int start = rnd.next(1, 1000000000 - 3 * n);
    int step = rnd.next(1, 3);
    for (int i = 0; i < n; ++i) {
        a[i] = start + i * step;
    }

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int changes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < changes; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    } else if (mode == 3) {
        vector<int> b;
        for (int i = 0; i < n; i += 2) b.push_back(a[i]);
        for (int i = 1; i < n; i += 2) b.push_back(a[i]);
        a = b;
    } else if (mode == 4) {
        rotate(a.begin(), a.begin() + rnd.next(1, n - 1), a.end());
    } else {
        reverse(a.begin(), a.end());
        int changes = rnd.next(n / 4, max(n / 4, n / 2));
        for (int i = 0; i < changes; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    }

    long long swaps = countSwaps(a, 0, n - 1);
    vector<int> kChoices = {1, 2, 3, 100000000};
    if (swaps > 0) {
        kChoices.push_back((int)rnd.next(1LL, swaps));
        kChoices.push_back((int)swaps);
        if (swaps < 100000000) kChoices.push_back((int)swaps + 1);
    }

    int k = rnd.any(kChoices);

    println(n, k);
    println(a);

    return 0;
}
