#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 1) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(5, 20);
    }

    vector<int> a(n);
    int start = rnd.next(1, 1000000000 - n + 1);
    for (int i = 0; i < n; ++i) {
        a[i] = start + i;
    }

    if (mode == 0) {
        // Already sorted: fewer than K swaps for every valid K.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, min(n - 1, 6));
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 2);
            int right = rnd.next(left + 1, n - 1);
            swap(a[left], a[right]);
        }
    } else if (mode == 3) {
        shuffle(a.begin(), a.end());
    } else {
        int rotations = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + rotations, a.end());
    }

    int k;
    if (mode == 0) {
        k = rnd.next(1, n);
    } else {
        k = rnd.next(1, n);
        if (rnd.next(0, 3) == 0) {
            k = n;
        }
    }

    println(n, k);
    println(a);
    return 0;
}
