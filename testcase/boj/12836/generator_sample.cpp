#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;

    if (mode == 0) {
        n = rnd.next(1, 5);
        q = 0;
    } else if (mode == 1) {
        n = 1;
        q = rnd.next(1, 25);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        q = rnd.next(10, 40);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
        q = rnd.next(20, 80);
    } else if (mode == 4) {
        n = rnd.next(9000, 10000);
        q = rnd.next(20, 80);
    } else {
        n = rnd.next(2, 20);
        q = rnd.next(1, 100);
    }

    println(n, q);

    vector<int> hotDays;
    hotDays.push_back(1);
    if (n > 1) hotDays.push_back(n);
    hotDays.push_back(rnd.next(1, n));
    hotDays.push_back(rnd.next(1, n));

    for (int i = 0; i < q; ++i) {
        bool makeUpdate;
        if (mode == 1) {
            makeUpdate = rnd.next(0, 99) < 70;
        } else if (mode == 5) {
            makeUpdate = (i % 3 != 2);
        } else {
            makeUpdate = rnd.next(0, 99) < 55;
        }

        if (makeUpdate) {
            int p = rnd.next(0, 99) < 60 ? rnd.any(hotDays) : rnd.next(1, n);
            long long x;
            int valueMode = rnd.next(0, 5);
            if (valueMode == 0) {
                x = rnd.any(vector<long long>{-2000000000LL, -1999999999LL, -1LL, 0LL, 1LL, 1999999999LL, 2000000000LL});
            } else if (valueMode <= 2) {
                x = rnd.next(-1000, 1000);
            } else {
                x = rnd.next(-2000000000LL, 2000000000LL);
            }
            println(1, p, x);
        } else {
            int l;
            int r;
            int rangeMode = rnd.next(0, 4);
            if (rangeMode == 0) {
                l = r = rnd.next(1, n);
            } else if (rangeMode == 1) {
                l = 1;
                r = n;
            } else if (rangeMode == 2) {
                l = rnd.any(hotDays);
                r = rnd.next(l, n);
            } else {
                l = rnd.next(1, n);
                r = rnd.next(l, n);
            }
            println(2, l, r);
        }
    }

    return 0;
}
