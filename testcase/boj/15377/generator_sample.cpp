#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampN(long long value) {
    return static_cast<int>(max(1LL, min(1000000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> ns;
    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 20);

    if (mode == 0) {
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.next(1, 50));
        }
    } else if (mode == 1) {
        int base = rnd.next(1, 1000);
        for (int i = 0; i < t; ++i) {
            ns.push_back(clampN(base + rnd.next(-10, 10)));
        }
    } else if (mode == 2) {
        vector<int> factors = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        long long value = 1;
        while (value <= 500000000 && rnd.next(0, 1)) {
            value *= rnd.any(factors);
        }
        for (int i = 0; i < t; ++i) {
            long long multiplier = rnd.next(1, 20);
            ns.push_back(clampN(value * multiplier - 1));
        }
    } else if (mode == 3) {
        for (int i = 0; i < t; ++i) {
            int bit = rnd.next(1, 29);
            long long value = (1LL << bit) + rnd.next(-5, 5);
            ns.push_back(clampN(value - 1));
        }
    } else if (mode == 4) {
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.next(999999900, 1000000000));
        }
    } else {
        ns = {1, 2, 3, 4, 5, 6, 10, 11, 12, 29, 30, 999, 1000, 999999999, 1000000000};
        shuffle(ns.begin(), ns.end());
        ns.resize(rnd.next(1, static_cast<int>(ns.size())));
    }

    println(static_cast<int>(ns.size()));
    for (int n : ns) {
        println(n);
    }

    return 0;
}
