#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(-1000000000LL, 1000000000LL));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        long long lo = rnd.next(-10LL, 0LL);
        long long hi = rnd.next(0LL, 10LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) a.push_back(-1);
            else if (pick == 1) a.push_back(0);
            else if (pick == 2) a.push_back(1);
            else if (pick == 3) a.push_back(rnd.next(-3LL, 3LL));
            else a.push_back(rnd.next(-20LL, 20LL));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        long long base = rnd.next(-1000LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + rnd.next(-2LL, 2LL));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            long long magnitude = rnd.next(999999990LL, 1000000000LL);
            a.push_back(rnd.next(0, 1) == 0 ? -magnitude : magnitude);
        }
    } else if (mode == 5) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            long long value = rnd.next(-100000LL, 100000LL);
            if (rnd.next(0, 3) == 0) value = -value;
            a.push_back(value);
        }
        sort(a.begin(), a.end());
    } else {
        n = rnd.next(30, 80);
        long long lo = rnd.next(-1000000000LL, 0LL);
        long long hi = rnd.next(0LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
