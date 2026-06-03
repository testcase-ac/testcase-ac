#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAX_SCORE = 100000000;

int clampScore(long long x) {
    return (int)max(0LL, min<long long>(MAX_SCORE, x));
}

int smallScore(int lo = 0, int hi = 40) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 12);
    int a = smallScore(0, 80);
    int b = smallScore(0, 80);
    vector<pair<int, int>> target(n);

    if (mode == 0) {
        a = rnd.next(70, 120);
        b = rnd.next(0, 20);
        for (auto& [l, r] : target) {
            l = smallScore(0, 20);
            r = smallScore(0, 20);
        }
    } else if (mode == 1) {
        a = rnd.next(0, 40);
        b = rnd.next(a + 1, 100);
        for (auto& [l, r] : target) {
            l = smallScore();
            r = smallScore();
        }
    } else if (mode == 2) {
        b = rnd.next(0, 40);
        int need = rnd.next(1, 40);
        a = b + need - 1;
        for (auto& [l, r] : target) {
            l = smallScore(0, max(0, need - 1));
            r = smallScore(0, max(0, need - 1));
        }
        int idx = rnd.next(n);
        if (rnd.next(0, 1) == 0) target[idx].first = need;
        else target[idx].second = need;
    } else if (mode == 3) {
        b = rnd.next(0, 40);
        int need = rnd.next(2, 60);
        a = b + need - 1;
        int i = rnd.next(n);
        int j = n == 1 ? i : rnd.next(n - 1);
        if (j >= i) ++j;
        int left = rnd.next(1, need - 1);
        int right = need - left;
        target[i].first = left;
        target[j].second = right;
        for (int k = 0; k < n; ++k) {
            if (k != i) target[k].first = smallScore(0, need + 5);
            if (k != j) target[k].second = smallScore(0, need + 5);
        }
    } else if (mode == 4) {
        a = rnd.next(1, 80);
        b = rnd.next(0, a - 1);
        int special = rnd.next(n);
        for (auto& [l, r] : target) {
            l = smallScore(0, 30);
            r = smallScore(0, 30);
        }
        target[special] = {rnd.next(a + 1 - b, min(MAX_SCORE, a + 30 - b)), rnd.next(0, 30)};
    } else if (mode == 5) {
        a = rnd.next(0, 20);
        b = rnd.next(0, 20);
        for (auto& [l, r] : target) {
            l = rnd.next(0, 1) == 0 ? 0 : smallScore(1, 10);
            r = rnd.next(0, 1) == 0 ? 0 : smallScore(1, 10);
        }
    } else if (mode == 6) {
        a = rnd.next(MAX_SCORE - 200, MAX_SCORE);
        b = rnd.next(MAX_SCORE - 200, MAX_SCORE);
        for (auto& [l, r] : target) {
            l = rnd.next(0, 1) == 0 ? MAX_SCORE : rnd.next(MAX_SCORE - 200, MAX_SCORE);
            r = rnd.next(0, 1) == 0 ? 0 : rnd.next(MAX_SCORE - 200, MAX_SCORE);
        }
    } else {
        n = rnd.next(8, 20);
        target.assign(n, {0, 0});
        a = rnd.next(0, 100);
        b = rnd.next(0, 100);
        int base = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            target[i].first = clampScore(base + rnd.next(-5, 20));
            target[i].second = clampScore(base + rnd.next(-5, 20));
        }
        shuffle(target.begin(), target.end());
    }

    println(a, b);
    println(n);
    for (auto [l, r] : target) {
        println(l, r);
    }

    return 0;
}
