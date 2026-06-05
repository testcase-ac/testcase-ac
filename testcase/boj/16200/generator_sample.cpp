#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<int> x;

    if (mode == 0) {
        n = rnd.next(1, 25);
        x.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        x.assign(n, n);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        int cap = rnd.next(2, min(n, 6));
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, cap);
            if (rnd.next(0, 4) == 0) value = n;
            x.push_back(value);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        int a = rnd.next(1, min(n, 3));
        int b = rnd.next(a, min(n, 6));
        for (int i = 0; i < n; ++i) x.push_back(rnd.any(vector<int>{a, b, n}));
    } else if (mode == 4) {
        n = rnd.next(4, 30);
        for (int i = 0; i < n; ++i) {
            int block = i % 5;
            if (block == 0) x.push_back(1);
            else if (block <= 2) x.push_back(min(n, 2));
            else x.push_back(min(n, 3));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 30);
        int pivot = rnd.next(2, min(n, 8));
        for (int i = 0; i < n; ++i) {
            int value = pivot + rnd.next(-1, 1);
            value = max(1, min(n, value));
            x.push_back(value);
        }
    } else {
        n = rnd.next(1, 30);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) x.push_back(rnd.next(lo, hi));
    }

    shuffle(x.begin(), x.end());

    println(n);
    println(x);

    return 0;
}
