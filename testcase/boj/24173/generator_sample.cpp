#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 35);
    vector<int> a(n);

    int start = rnd.next(1, 1000000000 - n * 1000);
    int step = rnd.next(1, 1000);
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
        for (int i = 0; i + 1 < n; i += 2) {
            swap(a[i], a[i + 1]);
        }
    } else if (mode == 4) {
        int high = a.back();
        for (int i = n - 1; i > 0; --i) {
            a[i] = a[i - 1];
        }
        a[0] = high;
    } else {
        int low = a.front();
        for (int i = 0; i + 1 < n; ++i) {
            a[i] = a[i + 1];
        }
        a.back() = low;
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, 20);
    } else if (kMode == 2) {
        k = rnd.next(21, 200);
    } else if (kMode == 3) {
        k = rnd.next(max(1, n - 3), n * 3);
    } else {
        k = 100000000;
    }

    println(n, k);
    println(a);

    return 0;
}
