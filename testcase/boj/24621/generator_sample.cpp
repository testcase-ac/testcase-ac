#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    return p;
}

static vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

static vector<int> rotatedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    if (n > 1) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
    }
    return p;
}

static vector<int> lightlyMixedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int swaps = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < swaps; ++i) {
        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 1);
        swap(p[x], p[y]);
    }
    return p;
}

static vector<int> blockPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int blockSize = rnd.next(1, min(n, 5));
    for (int l = 0; l < n; l += blockSize) {
        int r = min(n, l + blockSize);
        if (rnd.next(0, 1)) reverse(p.begin() + l, p.begin() + r);
        else shuffle(p.begin() + l, p.begin() + r);
    }
    return p;
}

static vector<int> makePermutation(int n, int mode) {
    vector<int> p;
    if (mode == 0) {
        p = identityPermutation(n);
    } else if (mode == 1) {
        p = identityPermutation(n);
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        p = rotatedPermutation(n);
    } else if (mode == 3) {
        p = lightlyMixedPermutation(n);
    } else if (mode == 4) {
        p = blockPermutation(n);
    } else {
        p = randomPermutation(n);
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(0, 4);
    int n;
    if (nMode == 0) {
        n = 1;
    } else if (nMode == 1) {
        n = rnd.next(2, 5);
    } else if (nMode == 2) {
        n = rnd.next(6, 12);
    } else if (nMode == 3) {
        n = rnd.next(13, 30);
    } else {
        n = rnd.next(31, 80);
    }

    int modeA = rnd.next(0, 5);
    int modeB = rnd.next(0, 5);
    vector<int> a = makePermutation(n, modeA);
    vector<int> b = makePermutation(n, modeB);

    if (rnd.next(0, 9) == 0) b = a;
    if (rnd.next(0, 9) == 0) {
        b = a;
        reverse(b.begin(), b.end());
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
