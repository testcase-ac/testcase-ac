#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(80, 250);
    } else {
        n = rnd.next(5, 25);
    }

    vector<int> a(n);
    int base = rnd.next(1, 1000000000 - n * 3);
    int step = rnd.next(1, 3);
    for (int i = 0; i < n; ++i) {
        a[i] = base + i * step;
    }

    if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(a[x], a[y]);
        }
    } else if (mode == 3) {
        int pivot = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + pivot, a.end());
    } else if (mode == 4) {
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = 1000000000 - i;
        }
        int tail = rnd.next(5, min(n, 30));
        shuffle(a.end() - tail, a.end());
    }

    int kMode = rnd.next(0, 3);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = rnd.next(1, min(n, 5));
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);
    println(a);

    return 0;
}
