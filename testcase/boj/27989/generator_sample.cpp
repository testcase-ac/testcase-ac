#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = 1000000000000LL;

long long smallValue(int lo = 1, int hi = 50) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 24);
    vector<long long> a;

    if (mode == 0) {
        long long cur = smallValue();
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(1, 8);
            a.push_back(cur);
        }
    } else if (mode == 1) {
        long long cur = smallValue(80, 160);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur = max(1LL, cur - rnd.next(1, 8));
        }
    } else if (mode == 2) {
        int blocks = rnd.next(1, 8);
        long long cur = smallValue();
        for (int b = 0; b < blocks; ++b) {
            cur += rnd.next(1, 10);
            int cnt = rnd.next(1, 4);
            while (cnt-- && (int)a.size() < n) {
                a.push_back(cur);
            }
        }
    } else if (mode == 3) {
        long long low = smallValue(1, 20);
        long long high = smallValue(70, 140);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a.push_back(low + rnd.next(0, 10));
                low += rnd.next(1, 5);
            } else {
                a.push_back(high - rnd.next(0, 10));
                high += rnd.next(1, 5);
            }
        }
    } else if (mode == 4) {
        int pivot = rnd.next(1, n);
        for (int i = 0; i < pivot; ++i) {
            a.push_back(MAX_A - pivot + i + 1);
        }
        for (int i = pivot; i < n; ++i) {
            a.push_back(rnd.next(1, 100));
        }
    } else if (mode == 5) {
        long long base = smallValue(1, 30);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + rnd.next(0, 4));
            if (rnd.next(0, 2) == 0) {
                base += rnd.next(0, 3);
            }
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 6) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(MAX_A - 100, MAX_A));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(smallValue(1, 200));
        }
    }

    println((int)a.size());
    println(a);

    return 0;
}
