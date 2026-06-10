#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int freshValue(set<int>& used, int lo, int hi) {
    int x = rnd.next(lo, hi);
    while (used.count(x)) {
        x = rnd.next(lo, hi);
    }
    used.insert(x);
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;
    set<int> used;

    if (mode == 0) {
        n = rnd.next(1, 2);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100000));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        int dominant = freshValue(used, 1, 100000);
        int cnt = n / 2 + 1;
        a.assign(cnt, dominant);
        while ((int)a.size() < n) {
            a.push_back(freshValue(used, 1, 100000));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        int x = freshValue(used, 1, 100000);
        int y = freshValue(used, 1, 100000);
        int cntX = n / 2;
        int cntY = n - cntX;
        a.assign(cntX, x);
        a.insert(a.end(), cntY, y);
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int kinds = rnd.next(3, min(n, 7));
        vector<int> values;
        for (int i = 0; i < kinds; ++i) {
            values.push_back(freshValue(used, 1, 100000));
        }
        vector<int> counts(kinds, 1);
        int remaining = n - kinds;
        while (remaining--) {
            vector<int> candidates;
            for (int i = 0; i < kinds; ++i) {
                if (counts[i] + 1 <= n / 2) {
                    candidates.push_back(i);
                }
            }
            int idx = rnd.any(candidates);
            ++counts[idx];
        }
        for (int i = 0; i < kinds; ++i) {
            a.insert(a.end(), counts[i], values[i]);
        }
    } else if (mode == 4) {
        n = rnd.next(6, 24);
        int lo = rnd.next(1, 99980);
        int hi = min(100000, lo + rnd.next(1, 20));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 25);
        int start = rnd.next(1, 99976);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + (i % 25));
        }
    } else {
        n = rnd.next(16, 35);
        int heavy = freshValue(used, 1, 100000);
        int cnt = rnd.next(max(1, n / 2 - 2), n / 2);
        a.assign(cnt, heavy);
        while ((int)a.size() < n) {
            int v = freshValue(used, 1, 100000);
            int copies = rnd.next(1, min(3, n - (int)a.size()));
            a.insert(a.end(), copies, v);
        }
        a.resize(n);
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
