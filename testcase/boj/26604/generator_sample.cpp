#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<long long> encodePermutation(const vector<int>& p) {
    int n = static_cast<int>(p.size());
    vector<long long> b(p.begin(), p.end());
    vector<int> prefix;

    for (int i = 0; i < n; ++i) {
        prefix.push_back(p[i]);
        sort(prefix.begin(), prefix.end());
        for (int j = 0; j <= i; ++j) {
            b[j] ^= prefix[j];
        }
    }

    return b;
}

vector<int> alternatingPermutation(int n) {
    vector<int> p;
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        if (rnd.next(2) == 0) {
            p.push_back(lo++);
            if (lo <= hi) {
                p.push_back(hi--);
            }
        } else {
            p.push_back(hi--);
            if (lo <= hi) {
                p.push_back(lo++);
            }
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 20) {
        n = 1;
    } else if (sizeMode < 45) {
        n = rnd.next(2, 5);
    } else if (sizeMode < 85) {
        n = rnd.next(6, 20);
    } else {
        n = rnd.next(21, 80);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    int mode = rnd.next(7);
    if (mode == 0) {
        // identity permutation
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(n)], p[rnd.next(n)]);
        }
    } else if (mode == 4) {
        int shift = rnd.next(n);
        rotate(p.begin(), p.begin() + shift, p.end());
    } else if (mode == 5) {
        p = alternatingPermutation(n);
    } else {
        int block = rnd.next(1, max(1, min(n, 8)));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            shuffle(p.begin() + l, p.begin() + r);
        }
        if (rnd.next(2) == 0) {
            reverse(p.begin(), p.end());
        }
    }

    vector<long long> b = encodePermutation(p);
    println(n);
    println(b);

    return 0;
}
