#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 24);
    vector<int> a;

    if (mode == 0) {
        int x = rnd.next(1, 1000000);
        a.assign(n, x);
    } else if (mode == 1) {
        n = rnd.next(5, 14);
        int keep = n - 2;
        int terms = keep - 1;
        int cap = min(1000000 / terms, 50000);
        int sum = 0;
        for (int i = 0; i < terms; ++i) {
            int x = rnd.next(1, cap);
            a.push_back(x);
            sum += x;
        }
        a.push_back(sum);
        a.push_back(rnd.next(1, 1000000));
        a.push_back(rnd.next(1, 1000000));
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        int base = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3);
            a.push_back(max(1, base + delta));
        }
        a[rnd.next(n)] = rnd.next(1, 1000000);
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        int small = rnd.next(1, 20);
        int large = rnd.next(900000, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 2) == 0 ? small : large - rnd.next(0, 20));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 22);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100));
        }
        int i = rnd.next(n);
        int j = rnd.next(n - 1);
        if (j >= i) ++j;
        a[i] = rnd.next(999000, 1000000);
        a[j] = rnd.next(999000, 1000000);
    } else {
        int hi = rnd.next(10, 1000000);
        int lo = rnd.next(1, min(hi, 1000));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    println((int)a.size());
    println(a);
    return 0;
}
