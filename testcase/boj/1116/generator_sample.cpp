#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    return p;
}

static vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

static vector<int> singleCyclePermutation(int n) {
    vector<int> order = randomPermutation(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[order[i]] = order[(i + 1) % n];
    }
    return p;
}

static vector<int> multiCyclePermutation(int n) {
    vector<int> order = randomPermutation(n);
    vector<int> p(n, -1);

    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int len = rnd.next(1, remaining);
        if (remaining > 1 && len == remaining - 1) {
            ++len;
        }

        for (int i = 0; i < len; ++i) {
            p[order[pos + i]] = order[pos + (i + 1) % len];
        }
        pos += len;
    }

    return p;
}

static void applyRandomSwaps(vector<int>& p, int maxSwaps) {
    int n = int(p.size());
    int swaps = rnd.next(1, maxSwaps);
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(n);
        int b = rnd.next(n);
        swap(p[a], p[b]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (rnd.next(100) < 75) {
        n = rnd.next(1, 14);
    } else {
        n = rnd.next(15, 50);
    }

    vector<int> p;
    if (mode == 0) {
        p = randomPermutation(n);
    } else if (mode == 1) {
        p = identityPermutation(n);
        if (n > 1) {
            applyRandomSwaps(p, min(n, 4));
        }
    } else if (mode == 2) {
        p = singleCyclePermutation(n);
    } else if (mode == 3) {
        p = multiCyclePermutation(n);
    } else if (mode == 4) {
        p = identityPermutation(n);
        reverse(p.begin(), p.end());
        if (n > 2 && rnd.next(2)) {
            applyRandomSwaps(p, min(n, 3));
        }
    } else {
        p = singleCyclePermutation(n);
        if (n > 1) {
            applyRandomSwaps(p, min(n, 5));
        }
    }

    println(n);
    println(p);
    return 0;
}
