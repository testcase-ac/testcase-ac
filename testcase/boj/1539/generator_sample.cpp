#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static void appendBalanced(vector<int>& order, int lo, int hi) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2;
    order.push_back(mid);
    appendBalanced(order, lo, mid - 1);
    appendBalanced(order, mid + 1, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        p.clear();
        appendBalanced(p, 0, n - 1);
    } else if (mode == 4) {
        p.clear();
        int lo = 0;
        int hi = n - 1;
        bool takeHi = rnd.next(0, 1);
        while (lo <= hi) {
            if (takeHi) {
                p.push_back(hi--);
            } else {
                p.push_back(lo++);
            }
            takeHi = !takeHi;
        }
    } else if (mode == 5) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(max(0, a - 3), min(n - 1, a + 3));
            swap(p[a], p[b]);
        }
    } else if (mode == 6) {
        int block = rnd.next(2, min(n, 10));
        for (int start = 0; start < n; start += block) {
            int finish = min(n, start + block);
            if (rnd.next(0, 1)) {
                reverse(p.begin() + start, p.begin() + finish);
            } else {
                shuffle(p.begin() + start, p.begin() + finish);
            }
        }
    }

    println(n);
    for (int value : p) {
        println(value);
    }

    return 0;
}
