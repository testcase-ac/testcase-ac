#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100000, x));
}

void addRun(vector<int>& xs, int start, int len, int maxCopies) {
    for (int i = 0; i < len; ++i) {
        int copies = rnd.next(1, maxCopies);
        for (int j = 0; j < copies; ++j) xs.push_back(clampValue(start + i));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> xs;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        xs.push_back(rnd.any(vector<int>{1, 2, 99999, 100000}));
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        int value = rnd.next(1, 100000);
        xs.assign(n, value);
    } else if (mode == 2) {
        int len = rnd.next(2, 18);
        int start = rnd.next(1, 100000 - len + 1);
        addRun(xs, start, len, rnd.next(1, 4));
    } else if (mode == 3) {
        int blocks = rnd.next(2, 5);
        int cur = rnd.next(1, 30);
        for (int b = 0; b < blocks; ++b) {
            int len = rnd.next(1, 8);
            addRun(xs, cur, len, rnd.next(1, 3));
            cur += len + rnd.next(1, 8);
        }
    } else if (mode == 4) {
        int n = rnd.next(8, 50);
        for (int i = 0; i < n; ++i) {
            xs.push_back(rnd.next(99980, 100000));
        }
    } else if (mode == 5) {
        int n = rnd.next(8, 45);
        int lo = rnd.next(1, 80);
        int hi = lo + rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) xs.push_back(rnd.next(1, 100000));
            else xs.push_back(rnd.next(lo, hi));
        }
    } else {
        int len = rnd.next(4, 20);
        int start = rnd.next(1, 100000 - len + 1);
        for (int i = 0; i < len; ++i) {
            int copies = (i % 2 == 0) ? rnd.next(2, 5) : rnd.next(1, 2);
            for (int j = 0; j < copies; ++j) xs.push_back(start + i);
        }
    }

    shuffle(xs.begin(), xs.end());

    println((int)xs.size());
    println(xs);

    return 0;
}
