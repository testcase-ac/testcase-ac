#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static void applyAdjacentNoise(vector<int>& p, int swaps) {
    int n = static_cast<int>(p.size());
    if (n < 2) return;
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 2);
        swap(p[pos], p[pos + 1]);
    }
}

static vector<int> makeRanking(int n, int mode, int row) {
    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        if (rnd.next(0, 3) == 0) reverse(p.begin(), p.end());
    } else if (mode == 1) {
        int shift = (row + rnd.next(0, n - 1)) % n;
        rotate(p.begin(), p.begin() + shift, p.end());
    } else if (mode == 2) {
        reverse(p.begin(), p.end());
        applyAdjacentNoise(p, rnd.next(0, max(1, n / 2)));
    } else if (mode == 3) {
        applyAdjacentNoise(p, rnd.next(1, max(1, 2 * n)));
    } else if (mode == 4) {
        int blockSize = rnd.next(2, max(2, min(n, 5)));
        for (int start = 0; start < n; start += blockSize) {
            int finish = min(n, start + blockSize);
            if (rnd.next(0, 1) == 0) {
                reverse(p.begin() + start, p.begin() + finish);
            } else {
                shuffle(p.begin() + start, p.begin() + finish);
            }
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 5);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        k = rnd.next(2, 12);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        k = rnd.next(3, 15);
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        k = rnd.next(2, 20);
    } else {
        n = rnd.next(10, 60);
        k = rnd.next(5, 30);
    }

    println(n, k);
    for (int row = 0; row < k; ++row) {
        int rowMode = mode;
        if (mode == 5 || rnd.next(0, 4) == 0) rowMode = rnd.next(0, 5);
        println(makeRanking(n, rowMode, row));
    }

    return 0;
}
