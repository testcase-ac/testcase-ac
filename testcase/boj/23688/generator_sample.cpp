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

vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

vector<int> singleSwapPermutation(int n) {
    vector<int> p = identityPermutation(n);
    if (n >= 2) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) ++b;
        swap(p[a], p[b]);
    }
    return p;
}

vector<int> cycleBlockPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int len = rnd.next(1, n);
    int start = rnd.next(0, n - len);
    if (len >= 2) {
        int shift = rnd.next(1, len - 1);
        vector<int> block;
        for (int i = 0; i < len; ++i) {
            block.push_back(start + i + 1);
        }
        for (int i = 0; i < len; ++i) {
            p[start + i] = block[(i + shift) % len];
        }
    }
    return p;
}

vector<int> pairedSwapPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int start = rnd.next(0, 1);
    for (int i = start; i + 1 < n; i += 2) {
        if (rnd.next(0, 1)) {
            swap(p[i], p[i + 1]);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int m = rnd.next(1, 8);
    int q = rnd.next(1, 24);

    println(n, m, q);

    for (int i = 0; i < m; ++i) {
        int mode = rnd.next(0, 4);
        vector<int> p;
        if (mode == 0) {
            p = identityPermutation(n);
        } else if (mode == 1) {
            p = singleSwapPermutation(n);
        } else if (mode == 2) {
            p = cycleBlockPermutation(n);
        } else if (mode == 3) {
            p = pairedSwapPermutation(n);
        } else {
            p = randomPermutation(n);
        }
        println(p);
    }

    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 3);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (mode == 0) {
            b = a;
        } else if (mode == 1 && n >= 2) {
            b = a % n + 1;
        }
        println(a, b);
    }

    return 0;
}
