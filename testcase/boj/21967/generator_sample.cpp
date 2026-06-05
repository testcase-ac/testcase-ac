#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(60, 180);
    } else {
        n = rnd.next(2, 45);
    }

    vector<int> a;

    if (mode == 0) {
        a.push_back(rnd.next(1, 10));
    } else if (mode == 1) {
        int lo = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, lo + 2));
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 7);
        int high = rnd.next(low + 3, 10);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? low : high);
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 8);
        int bad = rnd.next(1, 10);
        while (bad >= lo && bad <= lo + 2) {
            bad = rnd.next(1, 10);
        }
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(4, 8) == 0) {
                a.push_back(bad);
            } else {
                a.push_back(rnd.next(lo, lo + 2));
            }
        }
    } else if (mode == 4) {
        int start = rnd.next(1, 10);
        int step = rnd.any(vector<int>{-1, 1});
        for (int i = 0; i < n; ++i) {
            int value = start + step * (i % 5);
            while (value < 1) value += 10;
            while (value > 10) value -= 10;
            a.push_back(value);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 70) {
                int lo = rnd.next(1, 8);
                a.push_back(rnd.next(lo, lo + 2));
            } else {
                a.push_back(rnd.next(1, 10));
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
