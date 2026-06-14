#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<int> s;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 6);
        int hi = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(1, hi));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(1, 20);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, 3) == 0 ? rnd.next(0, 25) : 0;
            s.push_back(base + delta);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 25);
        m = rnd.next(1, 50);
        int current = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(0, 7);
            s.push_back(current);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        m = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(1, 100000));
    } else if (mode == 4) {
        n = rnd.next(50000, 100000);
        m = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                s.push_back(100000);
            } else {
                s.push_back(rnd.next(1, 100000));
            }
        }
    } else {
        n = rnd.next(2, 30);
        m = rnd.next(2, 80);
        int small = rnd.next(1, 10);
        int large = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(0, 2) == 0 ? small : rnd.next(small, large));
        }
    }

    if (mode == 2 && rnd.next(0, 1)) reverse(s.begin(), s.end());
    if (rnd.next(0, 1)) shuffle(s.begin(), s.end());

    int maxScore = *max_element(s.begin(), s.end());
    long long maxA = min(10000000000LL, 1LL * m * maxScore);
    long long a;
    if (rnd.next(0, 5) == 0) {
        a = maxA;
    } else if (maxA <= 100) {
        a = rnd.next(1LL, maxA);
    } else {
        long long lo = rnd.next(0, 2) == 0 ? 1LL : max(1LL, maxA - rnd.next(0LL, min(1000LL, maxA - 1)));
        a = rnd.next(lo, maxA);
    }

    println(n, m, a);
    println(s);

    return 0;
}
