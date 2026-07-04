#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<pair<int, pair<int, int>>> hints;
    long long palindromeLengthSum = 0;

    auto addPalindrome = [&](int l, int r) {
        if (l > r) swap(l, r);
        palindromeLengthSum += r - l + 1;
        hints.push_back({1, {l, r}});
    };

    auto addDifferent = [&](int l, int r) {
        if (l > r) swap(l, r);
        hints.push_back({2, {l, r}});
    };

    if (mode == 0) {
        int m = rnd.next(1, 16);
        for (int q = 0; q < m; ++q) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            if (rnd.next(0, 1) == 0) {
                addPalindrome(l, r);
            } else {
                addDifferent(l, r);
            }
        }
    } else if (mode == 1) {
        int blocks = rnd.next(1, min(n, 6));
        for (int q = 0; q < blocks; ++q) {
            int l = rnd.next(1, n);
            int len = rnd.next(1, min(7, n - l + 1));
            addPalindrome(l, l + len - 1);
        }
        int extra = rnd.next(1, 8);
        for (int q = 0; q < extra; ++q) {
            addDifferent(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 99) < 85) {
                addDifferent(i, i + 1);
            }
        }
        int extra = rnd.next(1, 5);
        for (int q = 0; q < extra; ++q) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, min(n, l + 4));
            addPalindrome(l, r);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        int l = rnd.next(1, n - 2);
        int r = rnd.next(l + 2, n);
        addPalindrome(l, r);
        addDifferent(l, r);
        int extra = rnd.next(1, 8);
        for (int q = 0; q < extra; ++q) {
            if (rnd.next(0, 1) == 0) {
                int a = rnd.next(1, n);
                int b = rnd.next(a, min(n, a + 5));
                addPalindrome(a, b);
            } else {
                addDifferent(rnd.next(1, n), rnd.next(1, n));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        int selfDiffs = rnd.next(1, 3);
        for (int q = 0; q < selfDiffs; ++q) {
            int pos = rnd.next(1, n);
            addDifferent(pos, pos);
        }
        int extra = rnd.next(0, 6);
        for (int q = 0; q < extra; ++q) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            if (rnd.next(0, 1) == 0) {
                addPalindrome(l, r);
            } else {
                addDifferent(l, r);
            }
        }
    } else {
        n = rnd.next(8, 30);
        int center = rnd.next(2, n - 1);
        int radius = min({center - 1, n - center, rnd.next(1, 6)});
        addPalindrome(center - radius, center + radius);
        for (int pos = center - radius; pos < center; ++pos) {
            if (rnd.next(0, 1) == 0) {
                addDifferent(pos, pos + 1);
            }
        }
        int extra = rnd.next(1, 8);
        for (int q = 0; q < extra; ++q) {
            addDifferent(rnd.next(1, n), rnd.next(1, n));
        }
    }

    shuffle(hints.begin(), hints.end());

    println(n, int(hints.size()));
    for (auto hint : hints) {
        println(hint.first, hint.second.first, hint.second.second);
    }

    return 0;
}
