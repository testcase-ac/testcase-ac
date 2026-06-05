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

vector<int> rotatedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    if (n > 1) {
        rotate(p.begin(), p.begin() + rnd.next(1, n - 1), p.end());
    }
    return p;
}

vector<int> adjacentSwapPermutation(int n) {
    vector<int> p = identityPermutation(n);
    for (int i = rnd.next(0, 1); i + 1 < n; i += 2) {
        if (rnd.next(0, 1)) {
            swap(p[i], p[i + 1]);
        }
    }
    return p;
}

vector<int> blockReversedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int block = rnd.next(2, min(n, 8));
    for (int l = 0; l < n; l += block) {
        int r = min(n, l + block);
        if (rnd.next(0, 1)) {
            reverse(p.begin() + l, p.begin() + r);
        }
    }
    return p;
}

vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 6);
        } else {
            n = rnd.next(2, 30);
        }

        vector<int> p;
        if (mode == 0) {
            p = identityPermutation(n);
        } else if (mode == 1) {
            p = identityPermutation(n);
            reverse(p.begin(), p.end());
        } else if (mode == 2) {
            p = rotatedPermutation(n);
        } else if (mode == 3) {
            p = adjacentSwapPermutation(n);
        } else if (mode == 4) {
            p = blockReversedPermutation(n);
        } else {
            p = randomPermutation(n);
        }

        println(n);
        println(p);
    }

    return 0;
}
