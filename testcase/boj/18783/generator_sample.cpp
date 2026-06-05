#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    int m = rnd.next(1, min(20, n * 2));

    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = rnd.next(1, 5);
    } else if (kMode == 1) {
        k = rnd.next(6, 1000);
    } else if (kMode == 2) {
        k = rnd.next(999999900LL, 1000000000LL);
    } else {
        k = rnd.next(1, 1000000000);
    }

    vector<pair<int, int>> ops;
    if (mode == 0) {
        int center = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            int radius = rnd.next(1, max(center - 1, n - center));
            int l = max(1, center - radius);
            int r = min(n, center + radius);
            if (l == r) {
                if (l > 1) --l;
                else ++r;
            }
            ops.push_back({l, r});
        }
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(2, n);
            int l = rnd.next(1, n - len + 1);
            ops.push_back({l, l + len - 1});
        }
        sort(ops.begin(), ops.end(), [](const auto& a, const auto& b) {
            int lenA = a.second - a.first;
            int lenB = b.second - b.first;
            if (lenA != lenB) return lenA > lenB;
            return a.first < b.first;
        });
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            if (i % 3 == 0) {
                ops.push_back({1, n});
            } else {
                int l = rnd.next(1, n - 1);
                int r = rnd.next(l + 1, n);
                ops.push_back({l, r});
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, n - 1);
            int maxLen = min(5, n - l + 1);
            int len = rnd.next(2, maxLen);
            ops.push_back({l, l + len - 1});
        }
    } else if (mode == 4) {
        int block = rnd.next(2, min(n, 8));
        for (int i = 0; i < m; ++i) {
            int start = 1 + (i * block) % n;
            if (start == n) --start;
            int r = min(n, start + rnd.next(1, block - 1));
            ops.push_back({start, r});
        }
    } else {
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, n - 1);
            int r = rnd.next(l + 1, n);
            ops.push_back({l, r});
        }
        shuffle(ops.begin(), ops.end());
    }

    println(n, m, k);
    for (auto [l, r] : ops) {
        println(l, r);
    }

    return 0;
}
