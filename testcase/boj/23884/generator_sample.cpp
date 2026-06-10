#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 30);
    if (mode == 5) {
        n = rnd.next(31, 80);
    }

    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = n;
    } else {
        k = rnd.next(1, n);
    }

    vector<int> a(n);
    int base = rnd.next(1, 1000);
    int step = rnd.next(1, 20);
    for (int i = 0; i < n; ++i) {
        a[i] = base + i * step;
    }

    if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(a[x], a[y]);
        }
    } else if (mode == 4) {
        int pivot = rnd.next(1, n - 2);
        reverse(a.begin(), a.begin() + pivot);
        shuffle(a.begin() + pivot, a.end());
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = 1000000000 - i * step;
        }
        shuffle(a.begin(), a.end());
    }

    println(n, k);
    println(a);

    return 0;
}
