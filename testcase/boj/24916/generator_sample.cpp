#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeByGaps(int n, int start, const vector<int>& gaps) {
    vector<int> a(n);
    a[0] = start;
    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] + gaps[i - 1];
    }
    return a;
}

vector<int> makeCase(int mode, int n) {
    vector<int> gaps;
    gaps.reserve(max(0, n - 1));

    if (mode == 0) {
        int gap = rnd.next(1, 8);
        gaps.assign(max(0, n - 1), gap);
    } else if (mode == 1) {
        int gap = rnd.next(1, 3);
        for (int i = 1; i < n; ++i) {
            gaps.push_back(gap);
            gap = min(200000, gap * rnd.next(2, 3));
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            gaps.push_back(rnd.next(1, 5));
        }
    } else if (mode == 3) {
        int big = rnd.next(80, 300);
        for (int i = 1; i < n; ++i) {
            gaps.push_back((i % rnd.next(2, 4) == 0) ? big + rnd.next(0, 40) : rnd.next(1, 7));
        }
    } else {
        for (int i = 1; i < n; ++i) {
            gaps.push_back(rnd.next(1, 150));
        }
        shuffle(gaps.begin(), gaps.end());
    }

    int span = 0;
    for (int gap : gaps) {
        span += gap;
    }

    int lo = -1000000;
    int hi = 1000000 - span;
    int start;
    if (mode == 4 && rnd.next(2) == 0) {
        start = rnd.next(2) ? lo : hi;
    } else {
        start = rnd.next(lo, hi);
    }

    return makeByGaps(n, start, gaps);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int batchMode = rnd.next(4);
    int t;
    if (batchMode == 0) {
        t = 1;
    } else if (batchMode == 1) {
        t = rnd.next(2, 5);
    } else if (batchMode == 2) {
        t = rnd.next(6, 15);
    } else {
        t = 50;
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n;
        if (batchMode == 3) {
            n = rnd.next(1, 5);
        } else if (mode == 1) {
            n = rnd.next(2, 9);
        } else {
            n = rnd.next(1, 18);
        }

        vector<int> a;
        if (n == 1) {
            a.push_back(rnd.next(-1000000, 1000000));
        } else {
            a = makeCase(mode, n);
        }

        println(n);
        println(a);
    }

    return 0;
}
