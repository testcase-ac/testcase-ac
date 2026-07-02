#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    int k = 0;
    vector<int> h;
    h.reserve(n);

    auto addHeight = [&](int x) {
        h.push_back(min(1000000, max(1, x)));
    };

    if (mode == 0) {
        k = 0;
        int base = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 12);
            addHeight(base * multiplier);
        }
    } else if (mode == 1) {
        k = rnd.next(1, 20);
        int divisor = rnd.next(k + 1, k + 60);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                addHeight(divisor * rnd.next(1, 12) + k);
            } else {
                addHeight(rnd.next(1, 250));
            }
        }
        addHeight(divisor);
    } else if (mode == 2) {
        k = rnd.next(0, 999999);
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            addHeight(rnd.next(1, 1000000));
        }
    } else if (mode == 3) {
        k = rnd.next(0, 30);
        int groups = rnd.next(1, 6);
        for (int g = 0; g < groups; ++g) {
            int value = rnd.next(k + 1, 200);
            int copies = rnd.next(1, 5);
            for (int i = 0; i < copies; ++i) {
                addHeight(value);
            }
        }
    } else if (mode == 4) {
        k = rnd.next(999950, 999999);
        n = rnd.next(2, 18);
        addHeight(1);
        addHeight(k);
        addHeight(k + 1);
        addHeight(1000000);
        while ((int)h.size() < n) {
            addHeight(rnd.next(max(1, k - 20), 1000000));
        }
    } else {
        k = rnd.next(1, 100);
        int divisorCount = rnd.next(2, 6);
        vector<int> divisors;
        for (int i = 0; i < divisorCount; ++i) {
            divisors.push_back(rnd.next(k + 1, k + 120));
        }
        for (int i = 0; i < n; ++i) {
            int d = rnd.any(divisors);
            int q = rnd.next(0, 10);
            addHeight(d * q + k);
        }
        for (int d : divisors) {
            addHeight(d);
        }
    }

    shuffle(h.begin(), h.end());

    println((int)h.size(), k);
    println(h);

    return 0;
}
