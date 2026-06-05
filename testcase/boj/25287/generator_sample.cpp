#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
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
        p.clear();
        int lo = 1;
        int hi = n;
        while (lo <= hi) {
            p.push_back(hi--);
            if (lo <= hi) {
                p.push_back(lo++);
            }
        }
        return p;
    }

    if (mode == 3) {
        for (int i = 0; i + 1 < n; i += 2) {
            swap(p[i], p[i + 1]);
        }
        if (rnd.next(2) && n > 2) {
            reverse(p.begin(), p.begin() + rnd.next(2, n));
        }
        return p;
    }

    if (mode == 4) {
        int shift = rnd.next(0, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        return p;
    }

    if (mode == 5) {
        int block = rnd.next(2, min(n, 6));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            if (rnd.next(2)) {
                reverse(p.begin() + l, p.begin() + r);
            } else {
                shuffle(p.begin() + l, p.begin() + r);
            }
        }
        return p;
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    vector<vector<int>> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 7 ? tc : rnd.next(0, 6);
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 2;
        } else if (rnd.next(4) == 0) {
            n = rnd.next(15, 35);
        } else {
            n = rnd.next(3, 14);
        }

        tests.push_back(makePermutation(n, mode));
    }

    println((int)tests.size());
    for (const vector<int>& p : tests) {
        println((int)p.size());
        println(p);
    }

    return 0;
}
