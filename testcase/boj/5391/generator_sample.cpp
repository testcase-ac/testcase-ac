#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeLengths(int n, int m, int mode) {
    vector<int> x;
    x.reserve(n);

    if (mode == 0) {
        int lo = rnd.next(1, min(20, max(1, m / 3)));
        int hi = rnd.next(lo, 20);
        for (int i = 0; i < n; ++i) x.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        int target = rnd.next(max(1, m - 4), min(100, m + 8));
        int remaining = target;
        while ((int)x.size() + 1 < n && remaining > 20) {
            int take = rnd.next(1, min(20, remaining - 1));
            x.push_back(take);
            remaining -= take;
        }
        if ((int)x.size() < n) x.push_back(min(20, max(1, remaining)));
        while ((int)x.size() < n) x.push_back(rnd.next(1, 20));
        shuffle(x.begin(), x.end());
    } else if (mode == 2) {
        int heavy = rnd.next(max(1, min(20, m - 3)), 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 70) {
                x.push_back(heavy);
            } else {
                x.push_back(rnd.next(1, 6));
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            x.push_back((i % 2 == 0) ? rnd.next(1, 4) : rnd.next(15, 20));
        }
    } else {
        int base = rnd.next(1, min(20, max(1, m / rnd.next(2, 5))));
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            x.push_back(min(20, max(1, base + delta)));
        }
    }

    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 12);
    vector<vector<int>> allLengths;
    vector<int> ms, as, bs;
    allLengths.reserve(t);
    ms.reserve(t);
    as.reserve(t);
    bs.reserve(t);

    int totalN = 0;
    for (int tc = 0; tc < t; ++tc) {
        int remainingCases = t - tc;
        int remainingN = 220 - totalN;
        int maxN = max(1, remainingN - (remainingCases - 1));
        int n;
        if (tc == t - 1 && rnd.next(4) == 0) {
            n = rnd.next(80, max(80, maxN));
        } else {
            n = rnd.next(1, min(maxN, rnd.next(3, 28)));
        }

        int m;
        if (rnd.next(5) == 0) {
            m = rnd.any(vector<int>{15, 16, 20, 55, 100});
        } else {
            m = rnd.next(15, 100);
        }

        int mode = rnd.next(0, 4);
        vector<int> lengths = makeLengths(n, m, mode);

        int a, b;
        int penaltyMode = rnd.next(0, 3);
        if (penaltyMode == 0) {
            a = rnd.next(1, 5);
            b = rnd.next(200, 1000);
        } else if (penaltyMode == 1) {
            a = rnd.next(200, 1000);
            b = rnd.next(1, 5);
        } else if (penaltyMode == 2) {
            int v = rnd.next(1, 1000);
            a = v;
            b = rnd.next(max(1, v - 3), min(1000, v + 3));
        } else {
            a = rnd.next(1, 1000);
            b = rnd.next(1, 1000);
        }

        totalN += n;
        ms.push_back(m);
        as.push_back(a);
        bs.push_back(b);
        allLengths.push_back(lengths);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println((int)allLengths[tc].size(), ms[tc]);
        println(as[tc], bs[tc]);
        println(allLengths[tc]);
    }

    return 0;
}
