#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(0, 10000));
    } else if (mode == 1) {
        n = 2;
        int lo = rnd.next(0, 10000);
        int hi = rnd.next(lo, 10000);
        a = {lo, hi};
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        int value = rnd.next(0, 10000);
        a.assign(n, value);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        int lowCount = rnd.next(1, n - 2);
        int mid = rnd.next(0, 10000);
        int high = rnd.next(mid, 10000);
        a.assign(lowCount, rnd.next(0, mid));
        while ((int)a.size() < n - 1) a.push_back(mid);
        a.push_back(high);
    } else if (mode == 4) {
        n = rnd.next(3, 20);
        int highCount = rnd.next(1, n - 1);
        int low = rnd.next(0, 10000);
        int high = rnd.next(low, 10000);
        a.assign(n - highCount, low);
        while ((int)a.size() < n) a.push_back(high);
    } else if (mode == 5) {
        n = rnd.next(3, 30);
        int base = rnd.next(0, 9500);
        int width = rnd.next(0, 500);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(base, base + width));
    } else if (mode == 6) {
        n = rnd.next(3, 30);
        for (int i = 0; i < n - 1; ++i) a.push_back(rnd.next(0, 100));
        a.push_back(rnd.next(9000, 10000));
    } else {
        n = rnd.next(3, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(rnd.any(vector<int>{0, 1, 9999, 10000}));
            } else {
                a.push_back(rnd.next(0, 10000));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
