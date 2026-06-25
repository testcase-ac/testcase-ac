#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxCoord = 1000000000LL;
    int mode = rnd.next(0, 5);

    int n;
    int m;
    int q;

    if (mode == 0) {
        n = 1;
        m = 1;
        q = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        m = 1;
        q = rnd.next(1, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        m = n;
        q = rnd.next(1, 18);
    } else {
        n = rnd.next(2, 32);
        m = rnd.next(1, n);
        q = rnd.next(1, 24);
    }

    vector<long long> a(n);
    if (mode == 0) {
        a[0] = rnd.next(1LL, maxCoord);
    } else if (mode == 4) {
        long long cur = maxCoord - rnd.next(0, 5000) - n * 3LL;
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(1LL, 4LL);
            a[i] = cur;
        }
    } else {
        long long cur = rnd.next(1LL, 30LL);
        int gapLimit = (mode == 3 ? rnd.next(1, 3) : rnd.next(1, 100));
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                long long gap;
                if (mode == 5 && rnd.next(0, 3) == 0) {
                    gap = rnd.next(1000LL, 100000LL);
                } else {
                    gap = rnd.next(1LL, static_cast<long long>(gapLimit));
                }
                cur += gap;
            }
            a[i] = cur;
        }
    }

    vector<long long> candidates;
    candidates.push_back(0);
    candidates.push_back(maxCoord);
    candidates.push_back(a.back() - a.front());
    for (int len = m; len <= min(n, m + 3); ++len) {
        int l = rnd.next(0, n - len);
        long long width = a[l + len - 1] - a[l];
        candidates.push_back(width);
        if (width > 0) candidates.push_back(width - 1);
        if (width < maxCoord) candidates.push_back(width + 1);
    }
    for (int i = 0; i < n && static_cast<int>(candidates.size()) < q * 2 + 8; ++i) {
        for (int j = i; j < n && j < i + 4; ++j) {
            candidates.push_back(a[j] - a[i]);
        }
    }

    vector<long long> x(q);
    for (int i = 0; i < q; ++i) {
        if (!candidates.empty() && rnd.next(0, 99) < 70) {
            x[i] = candidates[rnd.next(0, static_cast<int>(candidates.size()) - 1)];
        } else {
            x[i] = rnd.next(0LL, min(maxCoord, max(1000LL, a.back() - a.front() + 20)));
        }
    }

    println(n, m, q);
    println(a);
    println(x);

    return 0;
}
