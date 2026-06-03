#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 6);
        int value = rnd.next(1, n);
        a.assign(n - 2, value);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n - 2; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 15);
        for (int i = 0; i < n - 2; ++i) {
            a.push_back(1 + (i % n));
        }
        if (rnd.next(2)) {
            shuffle(a.begin(), a.end());
        }
    } else if (mode == 3) {
        n = rnd.next(5, 15);
        for (int i = 0; i < n - 2; ++i) {
            a.push_back(n - (i % n));
        }
        if (rnd.next(2)) {
            shuffle(a.begin(), a.end());
        }
    } else if (mode == 4) {
        n = rnd.next(6, 18);
        int anchor = rnd.next(max(1, n - 3), n);
        for (int i = 0; i < n - 2; ++i) {
            if (rnd.next(100) < 70) {
                a.push_back(anchor);
            } else {
                a.push_back(rnd.next(1, n));
            }
        }
    } else {
        n = rnd.next(8, 20);
        int lowAnchor = rnd.next(1, min(n, 3));
        int highAnchor = rnd.next(max(1, n - 2), n);
        for (int i = 0; i < n - 2; ++i) {
            int choice = rnd.next(100);
            if (choice < 35) {
                a.push_back(lowAnchor);
            } else if (choice < 70) {
                a.push_back(highAnchor);
            } else {
                a.push_back(rnd.next(1, n));
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
