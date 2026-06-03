#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

vector<int> nearSortedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int swaps = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(n);
        int b = rnd.next(n);
        swap(p[a], p[b]);
    }
    return p;
}

vector<int> blockReversedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int block = rnd.next(2, max(2, min(n, 6)));
    for (int l = 0; l < n; l += block) {
        int r = min(n, l + block);
        if (rnd.next(0, 1)) reverse(p.begin() + l, p.begin() + r);
    }
    return p;
}

vector<int> interleavedRunsPermutation(int n) {
    vector<vector<int>> runs(3);
    for (int x = 1; x <= n; ++x) {
        runs[rnd.next(3)].push_back(x);
    }

    vector<int> p;
    for (int r = 0; r < 3; ++r) {
        if (rnd.next(0, 1)) reverse(runs[r].begin(), runs[r].end());
        for (int x : runs[r]) p.push_back(x);
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 18);
        vector<int> p = identityPermutation(n);

        int mode = rnd.next(0, 5);
        if (mode == 0) {
            p = identityPermutation(n);
        } else if (mode == 1) {
            reverse(p.begin(), p.end());
        } else if (mode == 2) {
            p = nearSortedPermutation(n);
        } else if (mode == 3) {
            p = blockReversedPermutation(n);
        } else if (mode == 4) {
            p = interleavedRunsPermutation(n);
        } else {
            shuffle(p.begin(), p.end());
        }

        println(n);
        println(p);
    }

    return 0;
}
