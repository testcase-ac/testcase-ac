#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> values(n);
    for (int& value : values) value = rnd.next(lo, hi);
    return values;
}

int clampAbility(int value) {
    return max(1, min(1000, value));
}

void shuffleBoth(vector<int>& a, vector<int>& b) {
    shuffle(a.begin(), a.end());
    shuffle(b.begin(), b.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a = randomArray(n, 1, 12);
        b = randomArray(n, 1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int base = rnd.next(2, 999);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-1, 1);
            a.push_back(clampAbility(base + delta));
            b.push_back(clampAbility(base + rnd.next(-1, 1)));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        int groups = rnd.next(1, min(5, n));
        vector<int> pool;
        for (int i = 0; i < groups; ++i) pool.push_back(rnd.next(1, 1000));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
            b.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int low = rnd.next(1, 400);
        int high = rnd.next(601, 1000);
        for (int i = 0; i < n; ++i) {
            bool aHigh = rnd.next(0, 1);
            a.push_back(aHigh ? rnd.next(high - 40, high) : rnd.next(low, low + 40));
            b.push_back(aHigh ? rnd.next(low, low + 40) : rnd.next(high - 40, high));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 20);
        int start = rnd.next(1, 1000 - n);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i);
            b.push_back(clampAbility(start + i + rnd.next(-2, 2)));
        }
    } else if (mode == 5) {
        n = rnd.next(20, 50);
        int lo = rnd.next(1, 900);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(20, 100)));
        a = randomArray(n, lo, hi);
        b = randomArray(n, lo, hi);
    } else {
        n = 50;
        a = randomArray(n, 1, 1000);
        b = randomArray(n, 1, 1000);
    }

    shuffleBoth(a, b);

    println(n);
    println(a);
    println(b);
    return 0;
}
