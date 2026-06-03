#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxA = 500000;
    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(2, 8);
        a.assign(n, rnd.next(1, 5));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(maxA, lo + rnd.next(0, 30)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(maxA - 20, maxA));
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        int low = rnd.next(1, 3);
        int high = rnd.next(maxA - 3, maxA);
        for (int i = 0; i < n; ++i) a.push_back((i % 2 == 0) ? low : high);
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 3);
            if (choice == 0) a.push_back(1);
            else if (choice == 1) a.push_back(maxA);
            else a.push_back(rnd.next(2, 1000));
        }
    } else if (mode == 5) {
        n = rnd.next(50, 120);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, maxA));
    } else {
        n = rnd.next(2, 25);
        int base = rnd.next(1, maxA);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, 10);
            a.push_back(max(1, min(maxA, base + (i % 2 == 0 ? delta : -delta))));
        }
    }

    println(n);
    println(a);
    return 0;
}
