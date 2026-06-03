#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> t;

    if (mode == 0) {
        n = 1;
        t.push_back(rnd.next(10, 30));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(10, 30));
    } else if (mode == 2) {
        n = rnd.next(9, 25);
        int lo = rnd.next(10, 22);
        int hi = rnd.next(lo, 30);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(lo, hi));
    } else if (mode == 3) {
        n = rnd.next(80, 120);
        for (int i = 0; i < n; ++i) t.push_back(rnd.any(vector<int>{10, 11, 29, 30}));
    } else if (mode == 4) {
        n = rnd.next(2, 18);
        int base = rnd.any(vector<int>{10, 12, 16, 20, 24, 28, 30});
        for (int i = 0; i < n; ++i) t.push_back(max(10, min(30, base + rnd.next(-2, 2))));
    } else {
        n = rnd.next(2, 12);
        int total = 8 * (n - 1);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i - 1;
            int lo = max(10, 24 - (total % 24) - remaining * 30);
            int hi = min(30, 47 - (total % 24) - remaining * 10);
            int x = lo <= hi ? rnd.next(lo, hi) : rnd.next(10, 30);
            t.push_back(x);
            total += x;
        }
    }

    println(n);
    println(t);
    return 0;
}
