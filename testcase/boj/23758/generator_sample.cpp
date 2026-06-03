#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedPowerNeighbor(int exponent) {
    int base = 1;
    for (int i = 0; i < exponent; ++i) base *= 2;

    int delta = rnd.next(-2, 2);
    long long value = static_cast<long long>(base) + delta;
    if (value < 1) value = 1;
    if (value > 1000000000LL) value = 1000000000LL;
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(7, 30);
    }

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        a.push_back(rnd.next(1, 1000000000));
    } else if (mode == 1) {
        int value = boundedPowerNeighbor(rnd.next(0, 29));
        a.assign(n, value);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a.push_back(boundedPowerNeighbor(rnd.next(0, 29)));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(1, 8));
            } else if (bucket == 1) {
                a.push_back(rnd.next(9, 1000));
            } else if (bucket == 2) {
                a.push_back(rnd.next(100000000, 1000000000));
            } else {
                a.push_back(rnd.any(vector<int>{1, 2, 3, 999999999, 1000000000}));
            }
        }
    } else if (mode == 4) {
        int loExp = rnd.next(0, 12);
        int hiExp = rnd.next(18, 29);
        for (int i = 0; i < n; ++i) {
            a.push_back(i < (n + 1) / 2 ? boundedPowerNeighbor(loExp) : boundedPowerNeighbor(hiExp));
        }
    } else {
        int low = rnd.next(1, 100);
        int high = rnd.next(1000000, 1000000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? rnd.next(1, low) : rnd.next(low, high));
        }
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        shuffle(a.begin(), a.end());
    } else if (order == 1) {
        sort(a.begin(), a.end());
    } else {
        sort(a.rbegin(), a.rend());
    }

    println(n);
    println(a);

    return 0;
}
