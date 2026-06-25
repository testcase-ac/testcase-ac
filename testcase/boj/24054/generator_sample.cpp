#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long insertionStoreCount(const vector<int>& a) {
    long long stores = 0;
    vector<int> sorted;
    sorted.reserve(a.size());

    for (int value : a) {
        int greater = 0;
        for (int existing : sorted) {
            if (existing > value) {
                ++greater;
            }
        }
        if (greater > 0) {
            stores += greater + 1;
        }
        sorted.insert(upper_bound(sorted.begin(), sorted.end(), value), value);
    }

    return stores;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 14);
    int mode = rnd.next(0, 6);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        // Already sorted: no insertion-sort stores happen.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int rotations = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + rotations, a.end());
    } else if (mode == 3) {
        int small = 1;
        int large = n;
        vector<int> zigzag;
        while (small <= large) {
            zigzag.push_back(large--);
            if (small <= large) {
                zigzag.push_back(small++);
            }
        }
        a = zigzag;
    } else if (mode == 4) {
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        int swaps = rnd.next(1, n / 2 + 1);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    } else {
        int block = rnd.next(2, min(5, n));
        for (int start = 0; start < n; start += block) {
            reverse(a.begin() + start, a.begin() + min(n, start + block));
        }
    }

    int multiplier = rnd.next(1, 1000);
    int offset = rnd.next(0, 1000);
    for (int& value : a) {
        value = value * multiplier + offset;
    }

    long long totalStores = insertionStoreCount(a);
    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1 && totalStores > 0) {
        k = rnd.next(1LL, totalStores);
    } else if (kMode == 2) {
        k = totalStores + rnd.next(1LL, 20LL);
    } else if (kMode == 3) {
        k = 1000000000000LL;
    } else {
        k = rnd.next(1LL, 50LL);
    }

    println(n, k);
    println(a);

    return 0;
}
