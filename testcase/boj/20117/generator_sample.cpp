#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 1000));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int value = rnd.next(1, 1000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) ? 1000 : 1);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        int lo = rnd.next(1, 970);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 30)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 8);
        for (int i = 0; i < n / 2; ++i) {
            int high = rnd.next(500, 1000);
            a.push_back(rnd.next(1, high));
            a.push_back(high);
        }
    } else if (mode == 5) {
        n = 2 * rnd.next(1, 8) + 1;
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 1000));
        }
        a.push_back(1000);
        ++n;
    } else {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.wnext(1000, rnd.next(-3, 3)) + 1);
        }
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        sort(a.begin(), a.end());
    } else if (order == 1) {
        sort(a.rbegin(), a.rend());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
