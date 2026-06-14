#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = (1 << 30) - 1;

int randomMask(int maxBit, int minBits, int maxBits) {
    int take = rnd.next(minBits, maxBits);
    vector<int> bits;
    for (int bit = 0; bit <= maxBit; ++bit) {
        bits.push_back(bit);
    }
    shuffle(bits.begin(), bits.end());

    int value = 0;
    for (int i = 0; i < take; ++i) {
        value |= 1 << bits[i];
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 40 : 18);
    vector<int> a;

    if (mode == 0) {
        a.push_back(MAX_A);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(1, min(MAX_A, 255)));
        }
    } else if (mode == 1) {
        int bit = rnd.next(0, 29);
        int base = 1 << bit;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(randomMask(min(29, bit + rnd.next(0, 3)), 1, min(4, bit + 1)));
            } else {
                a.push_back(base);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int bit = (i + rnd.next(0, 3)) % 30;
            int value = 1 << bit;
            if (rnd.next(0, 2) == 0) {
                value |= 1 << rnd.next(0, 29);
            }
            a.push_back(value);
        }
    } else if (mode == 3) {
        int width = rnd.next(10, 30);
        int full = (1 << width) - 1;
        for (int i = 0; i < n; ++i) {
            int holes = randomMask(width - 1, 1, min(width, 5));
            a.push_back(max(1, full ^ holes));
        }
    } else if (mode == 4) {
        int width = rnd.next(1, 12);
        int hi = (1 << width) - 1;
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, hi));
        }
    } else {
        int shared = randomMask(29, 1, 6);
        for (int i = 0; i < n; ++i) {
            int extra = randomMask(29, 1, 8);
            a.push_back(shared | extra);
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
