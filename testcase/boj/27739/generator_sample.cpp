#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    return a;
}

static void reverseSmallSegments(vector<int>& a, int maxLen) {
    int n = (int)a.size();
    for (int l = 0; l < n;) {
        int len = rnd.next(1, min(maxLen, n - l));
        if (rnd.next(2) == 0) {
            reverse(a.begin() + l, a.begin() + l + len);
        }
        l += len;
    }
}

static vector<int> makePermutation(int n, int mode) {
    vector<int> a = identityPermutation(n);

    if (mode == 0) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        reverseSmallSegments(a, rnd.next(2, min(n, 6)));
    } else if (mode == 3) {
        int shift = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 4) {
        vector<int> odds, evens;
        for (int x = 1; x <= n; ++x) {
            if (x % 2) {
                odds.push_back(x);
            } else {
                evens.push_back(x);
            }
        }
        if (rnd.next(2) == 0) {
            reverse(evens.begin(), evens.end());
        } else {
            reverse(odds.begin(), odds.end());
        }
        a.clear();
        a.insert(a.end(), odds.begin(), odds.end());
        a.insert(a.end(), evens.begin(), evens.end());
    } else if (mode == 5) {
        int block = rnd.next(2, min(n, 7));
        vector<vector<int>> blocks;
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            blocks.emplace_back(a.begin() + l, a.begin() + r);
        }
        shuffle(blocks.begin(), blocks.end());
        a.clear();
        for (const auto& b : blocks) {
            a.insert(a.end(), b.begin(), b.end());
        }
    } else {
        shuffle(a.begin(), a.end());
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 70) {
        n = rnd.next(3, 12);
    } else if (sizeMode < 95) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(100, 250);
    }

    int kMode = rnd.next(5);
    int k;
    if (kMode == 0) {
        k = 2;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = max(2, n / 2 + rnd.next(-1, 1));
    } else if (kMode == 3) {
        k = rnd.next(2, min(n, 6));
    } else {
        k = rnd.next(2, n);
    }

    vector<int> a = makePermutation(n, rnd.next(7));

    println(n, k);
    println(a);
    return 0;
}
