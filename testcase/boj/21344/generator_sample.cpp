#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 2;
    vector<int> t;

    if (mode == 0) {
        n = rnd.next(2, 5);
        int value = rnd.next(-5, 5);
        t.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int lo = rnd.next(-20, 10);
        int hi = lo + rnd.next(0, 12);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                t.push_back(rnd.any(vector<int>{-100000, 100000, -99999, 99999}));
            } else {
                t.push_back(rnd.next(-3, 3));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        int start = rnd.next(-50, 20);
        int step = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) t.push_back(start + i * step);
        if (rnd.next(0, 1)) reverse(t.begin(), t.end());
    } else if (mode == 4) {
        n = rnd.next(4, 18);
        int left = rnd.next(-100, -1);
        int right = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                t.push_back(0);
            } else if (rnd.next(0, 1)) {
                t.push_back(rnd.next(left, min(left + 10, -1)));
            } else {
                t.push_back(rnd.next(max(right - 10, 1), right));
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        vector<int> base;
        int distinct = rnd.next(2, 6);
        for (int i = 0; i < distinct; ++i) base.push_back(rnd.next(-30, 30));
        for (int i = 0; i < n; ++i) t.push_back(rnd.any(base));
    } else if (mode == 6) {
        n = rnd.next(20, 60);
        int center = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) t.push_back(center + rnd.next(-100, 100));
    } else {
        n = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(-100000, 100000));
    }

    shuffle(t.begin(), t.end());

    println(n);
    println(t);

    return 0;
}
