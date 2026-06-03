#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> makePermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static vector<int> interleavedNoCase(int n) {
    vector<int> p;
    for (int x = 1; x <= n; x += 2) {
        p.push_back(x);
    }
    for (int x = 2; x <= n; x += 2) {
        p.push_back(x);
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    int k = 1;
    vector<int> p;

    if (mode == 0) {
        n = 1;
        k = 1;
        p = {1};
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        k = 1;
        p = makePermutation(n);
        shuffle(p.begin(), p.end());
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        k = n;
        p = makePermutation(n);
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        n = rnd.next(3, 16);
        k = rnd.next(2, n - 1);
        p = makePermutation(n);

        int firstValue = rnd.next(1, n - k + 1);
        vector<int> block;
        for (int x = firstValue; x < firstValue + k; ++x) {
            block.push_back(x);
        }
        shuffle(block.begin(), block.end());

        vector<int> rest;
        vector<int> inBlock(n + 1, 0);
        for (int x : block) {
            inBlock[x] = 1;
        }
        for (int x = 1; x <= n; ++x) {
            if (!inBlock[x]) {
                rest.push_back(x);
            }
        }
        shuffle(rest.begin(), rest.end());

        int pos = rnd.next(0, n - k);
        p.clear();
        p.insert(p.end(), rest.begin(), rest.begin() + pos);
        p.insert(p.end(), block.begin(), block.end());
        p.insert(p.end(), rest.begin() + pos, rest.end());
    } else if (mode == 4) {
        n = rnd.next(5, 15);
        k = 3;
        p = interleavedNoCase(n);
        if (rnd.next(0, 1)) {
            reverse(p.begin(), p.end());
        }
    } else if (mode == 5) {
        n = rnd.next(6, 18);
        k = rnd.next(2, min(6, n));
        p = makePermutation(n);
        shuffle(p.begin(), p.end());
    } else if (mode == 6) {
        n = rnd.next(8, 22);
        k = rnd.next(2, min(8, n - 1));
        p = makePermutation(n);

        int start = rnd.next(1, n - k + 1);
        vector<int> block;
        for (int x = start; x < start + k; ++x) {
            block.push_back(x);
        }
        if (rnd.next(0, 1)) {
            reverse(block.begin(), block.end());
        } else {
            shuffle(block.begin(), block.end());
        }

        vector<int> rest;
        for (int x = 1; x <= n; ++x) {
            if (x < start || x >= start + k) {
                rest.push_back(x);
            }
        }
        shuffle(rest.begin(), rest.end());
        p = rest;
        int pos = rnd.next(0, (int)p.size());
        p.insert(p.begin() + pos, block.begin(), block.end());
    } else {
        n = rnd.next(12, 28);
        k = rnd.next(2, min(10, n));
        p = makePermutation(n);
        int chunk = rnd.next(2, min(5, n));
        for (int l = 0; l < n; l += chunk) {
            int r = min(n, l + chunk);
            if (rnd.next(0, 1)) {
                reverse(p.begin() + l, p.begin() + r);
            } else {
                shuffle(p.begin() + l, p.begin() + r);
            }
        }
        if (rnd.next(0, 1)) {
            shuffle(p.begin(), p.end());
        }
    }

    println(n, k);
    println(p);
    return 0;
}
