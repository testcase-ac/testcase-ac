#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MAX_A = 1000000000;

static int clampSkill(long long x) {
    if (x < 1) return 1;
    if (x > MAX_A) return MAX_A;
    return static_cast<int>(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(3, 25);
    if (n % 2 == 0) ++n;

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int value = rnd.any(vector<int>{1, 2, 999999999, MAX_A, rnd.next(1, MAX_A)});
        a.assign(n, value);
    } else if (mode == 1) {
        int lo = rnd.next(1, 200);
        int hi = rnd.next(lo, min(MAX_A, lo + rnd.next(0, 30)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        int start = rnd.next(1, MAX_A - 200);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(clampSkill(1LL * start + 1LL * i * step));
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 20);
        int high = rnd.next(MAX_A - 20, MAX_A);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(rnd.next(1, 5));
            } else if (i % 3 == 1) {
                a.push_back(rnd.next(MAX_A - 4, MAX_A));
            } else {
                a.push_back(rnd.next(low, high));
            }
        }
    } else if (mode == 4) {
        int center = rnd.next(50, MAX_A - 50);
        int spread = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            a.push_back(clampSkill(1LL * center + rnd.next(-spread, spread)));
        }
    } else if (mode == 5) {
        int pairSum = rnd.next(100, MAX_A);
        for (int i = 0; i < n - 1; i += 2) {
            int x = rnd.next(1, max(1, pairSum - 1));
            int y = clampSkill(1LL * pairSum - x + rnd.next(-3, 3));
            a.push_back(x);
            a.push_back(y);
        }
        a.push_back(rnd.next(1, MAX_A));
    } else {
        n = rnd.next(27, 81);
        if (n % 2 == 0) ++n;
        int buckets = rnd.next(2, 6);
        vector<int> values;
        for (int i = 0; i < buckets; ++i) {
            values.push_back(rnd.any(vector<int>{
                rnd.next(1, 100),
                rnd.next(1000, 1000000),
                rnd.next(MAX_A - 1000, MAX_A),
            }));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(values));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
