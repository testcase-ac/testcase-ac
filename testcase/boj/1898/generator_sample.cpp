#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 85) {
        n = rnd.next(3, 30);
    } else {
        n = rnd.next(31, 200);
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);

    int mode = rnd.next(6);
    if (mode == 0) {
        // Identity permutation.
    } else if (mode == 1) {
        reverse(perm.begin(), perm.end());
    } else if (mode == 2) {
        int start = rnd.next(2);
        for (int i = start; i + 1 < n; i += 2) {
            swap(perm[i], perm[i + 1]);
        }
        if (rnd.next(2)) {
            reverse(perm.begin(), perm.end());
        }
    } else if (mode == 3) {
        int shift = rnd.next(1, n - 1);
        rotate(perm.begin(), perm.begin() + shift, perm.end());
    } else if (mode == 4) {
        int blockSize = rnd.next(2, min(n, 8));
        for (int left = 0; left < n; left += blockSize) {
            int right = min(n, left + blockSize);
            shuffle(perm.begin() + left, perm.begin() + right);
        }
        if (rnd.next(2)) {
            reverse(perm.begin(), perm.end());
        }
    } else {
        shuffle(perm.begin(), perm.end());
    }

    println(n);
    for (int value : perm) {
        println(value);
    }

    return 0;
}
