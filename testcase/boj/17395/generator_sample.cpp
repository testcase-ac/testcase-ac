#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomBitsFrom(const vector<int>& bits) {
    long long x = 0;
    for (int bit : bits) {
        x |= 1LL << bit;
    }
    return x;
}

int popcountLong(long long x) {
    int count = 0;
    while (x > 0) {
        count += x & 1LL;
        x >>= 1;
    }
    return count;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long limit = 10000000000000000LL;
    int mode = rnd.next(0, 5);
    long long x0 = 1;

    if (mode == 0) {
        int bit = rnd.next(0, 53);
        x0 = 1LL << bit;
    } else if (mode == 1) {
        int high = rnd.next(1, 20);
        x0 = (1LL << high) - 1;
    } else if (mode == 2) {
        vector<int> bits;
        int highest = rnd.next(1, 53);
        bits.push_back(highest);
        int extra = rnd.next(0, min(8, highest));
        for (int i = 0; i < extra; ++i) {
            int bit = rnd.next(0, highest - 1);
            if (find(bits.begin(), bits.end(), bit) == bits.end()) {
                bits.push_back(bit);
            }
        }
        x0 = randomBitsFrom(bits);
    } else if (mode == 3) {
        x0 = limit - rnd.next(0LL, 2000LL);
    } else if (mode == 4) {
        int blocks = rnd.next(1, 8);
        for (int i = 0; i < blocks; ++i) {
            int bit = rnd.next(0, 53);
            x0 |= 1LL << bit;
        }
    } else {
        x0 = rnd.next(1LL, 200000LL);
    }

    x0 = max(1LL, min(x0, limit));

    int ones = popcountLong(x0);
    int n;
    int nMode = rnd.next(0, 3);
    if (nMode == 0) {
        n = rnd.next(1, min(50, max(1, ones)));
    } else if (nMode == 1 && ones < 50) {
        n = rnd.next(ones + 1, 50);
    } else {
        n = rnd.next(1, 50);
    }

    println(x0, n);
    return 0;
}
