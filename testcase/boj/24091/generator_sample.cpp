#include "testlib.h"

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode <= 3) {
        n = rnd.next(5, 18);
    } else if (mode <= 5) {
        n = rnd.next(19, 60);
    } else {
        n = rnd.next(100, 220);
    }

    vector<int> a(n);
    int base = rnd.next(1, 1000000000 - 3 * n);
    for (int i = 0; i < n; ++i) {
        a[i] = base + 3 * i;
    }

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        rotate(a.begin(), a.begin() + rnd.next(1, n - 1), a.end());
    } else if (mode == 3) {
        shuffle(a.begin(), a.end());
        int pivotRank = rnd.next(1, n - 2);
        nth_element(a.begin(), a.begin() + pivotRank, a.end());
        swap(a[pivotRank], a.back());
    } else if (mode == 4) {
        shuffle(a.begin(), a.end());
        sort(a.begin(), a.begin() + n / 2);
    } else if (mode == 5) {
        shuffle(a.begin(), a.end());
        sort(a.begin() + n / 2, a.end(), greater<int>());
    } else {
        shuffle(a.begin(), a.end());
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = rnd.next(1, min(20, n));
    } else if (kMode == 1) {
        k = rnd.next(n, min(100000000, n * 12));
    } else if (kMode == 2) {
        k = rnd.next(1000000, 100000000);
    } else if (kMode == 3) {
        k = 1;
    } else {
        k = 100000000;
    }

    println(n, k);
    println(a);
    return 0;
}
