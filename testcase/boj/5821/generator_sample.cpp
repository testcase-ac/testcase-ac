#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r;
    int l;
    long long b;
    vector<int> x;

    if (mode == 0) {
        r = rnd.next(1, 8);
        l = rnd.next(1, 25);
        b = rnd.next(0LL, 30LL);
        x.resize(r);
        for (int i = 0; i < r; ++i) {
            x[i] = rnd.next(1, l);
        }
    } else if (mode == 1) {
        r = rnd.next(5, 14);
        l = rnd.next(20, 80);
        b = rnd.next(0LL, 120LL);
        int center = rnd.next(1, l);
        int radius = rnd.next(0, min(l - 1, 8));
        x.resize(r);
        for (int i = 0; i < r; ++i) {
            int lo = max(1, center - radius);
            int hi = min(l, center + radius);
            x[i] = rnd.next(lo, hi);
        }
    } else if (mode == 2) {
        r = rnd.next(6, 14);
        l = rnd.next(50, 300);
        b = rnd.next(0LL, 500LL);
        x.push_back(1);
        x.push_back(l);
        while ((int)x.size() < r) {
            x.push_back(rnd.next(1, l));
        }
    } else if (mode == 3) {
        r = rnd.next(8, 18);
        l = rnd.next(100, 10000);
        b = rnd.any(vector<long long>{0LL, 1LL, rnd.next(2LL, 1000LL)});
        int cur = rnd.next(1, min(l, 10));
        for (int i = 0; i < r; ++i) {
            cur = min(l, cur + rnd.next(0, max(1, l / 20)));
            x.push_back(cur);
        }
    } else if (mode == 4) {
        r = rnd.next(10, 25);
        l = rnd.next(100000000, 1000000000);
        b = rnd.next(1000000000000LL, 2000000000000000LL);
        for (int i = 0; i < r; ++i) {
            x.push_back(rnd.next(1, l));
        }
    } else {
        r = rnd.next(12, 25);
        l = rnd.next(20, 120);
        b = rnd.next(0LL, 2000LL);
        vector<int> anchors;
        int anchorCount = rnd.next(2, 5);
        for (int i = 0; i < anchorCount; ++i) {
            anchors.push_back(rnd.next(1, l));
        }
        for (int i = 0; i < r; ++i) {
            int anchor = rnd.any(anchors);
            int shift = rnd.next(-3, 3);
            x.push_back(min(l, max(1, anchor + shift)));
        }
    }

    sort(x.begin(), x.end());

    println(r, l, b);
    for (int value : x) {
        println(value);
    }

    return 0;
}
