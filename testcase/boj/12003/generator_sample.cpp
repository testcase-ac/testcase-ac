#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampSize(long long x) {
    return (int)max(1LL, min(1000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long k;
    vector<int> sizes;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(0, 4);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            sizes.push_back(clampSize(base + rnd.next(0, (int)k)));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        k = rnd.next(0, 8);
        int leftBase = rnd.next(1, 100);
        int gap = (int)k + rnd.next(1, 20);
        int rightBase = leftBase + gap;
        for (int i = 0; i < n; ++i) {
            int base = (i < n / 2) ? leftBase : rightBase;
            sizes.push_back(clampSize(base + rnd.next(0, (int)k)));
        }
    } else if (mode == 2) {
        n = rnd.next(6, 28);
        k = rnd.next(1, 12);
        int base = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            long long offset = 1LL * rnd.next(0, 5) * (k + 1) + rnd.next(0, (int)k);
            sizes.push_back(clampSize(base + offset));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 35);
        k = 0;
        int distinct = rnd.next(1, min(n, 7));
        vector<int> values;
        for (int i = 0; i < distinct; ++i) values.push_back(rnd.next(1, 80));
        for (int i = 0; i < n; ++i) sizes.push_back(rnd.any(values));
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        k = rnd.any(vector<long long>{0LL, 1LL, 999999999LL, 1000000000LL});
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                sizes.push_back(rnd.any(vector<int>{1, 2, 999999999, 1000000000}));
            } else {
                sizes.push_back(rnd.next(1, 1000000000));
            }
        }
    } else {
        n = rnd.next(8, 40);
        k = rnd.next(1, 30);
        int base = rnd.next(1, 500);
        for (int i = 0; i < n; ++i) {
            long long offset = i * rnd.next(0, 3) + rnd.next(0, (int)k + 2);
            sizes.push_back(clampSize(base + offset));
        }
    }

    shuffle(sizes.begin(), sizes.end());

    println(n, k);
    for (int size : sizes) println(size);

    return 0;
}
