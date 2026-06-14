#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    return p;
}

vector<int> alternatingLowHigh(int n) {
    vector<int> p;
    int lo = 1, hi = n;
    while (lo <= hi) {
        if (rnd.next(2)) {
            p.push_back(lo++);
            if (lo <= hi) p.push_back(hi--);
        } else {
            p.push_back(hi--);
            if (lo <= hi) p.push_back(lo++);
        }
    }
    return p;
}

vector<int> blockPermutation(int n) {
    vector<int> p;
    int next = 1;
    while (next <= n) {
        int len = rnd.next(1, min(6, n - next + 1));
        vector<int> block;
        for (int i = 0; i < len; ++i) block.push_back(next + i);
        if (rnd.next(2)) reverse(block.begin(), block.end());
        for (int value : block) p.push_back(value);
        next += len;
    }
    if (rnd.next(2)) {
        int shift = rnd.next(0, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
    }
    return p;
}

vector<int> makePermutation(int n, int mode) {
    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        return p;
    }
    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }
    if (mode == 2) {
        shuffle(p.begin(), p.end());
        return p;
    }
    if (mode == 3) {
        p = alternatingLowHigh(n);
        return p;
    }
    if (mode == 4) {
        return blockPermutation(n);
    }

    int swaps = rnd.next(1, max(1, n / 3));
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(max(0, a - 3), min(n - 1, a + 3));
        swap(p[a], p[b]);
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (tc == 0) {
            n = rnd.next(1, 3);
        } else if (mode <= 1) {
            n = rnd.next(2, 35);
        } else {
            n = rnd.next(4, 60);
        }

        vector<int> p = makePermutation(n, mode);
        println(n);
        for (int value : p) println(value);
    }

    return 0;
}
