#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_K = 1000000;
    vector<int> powers;
    for (int x = 1; x <= 1 << 20; x <<= 1) powers.push_back(x);

    int mode = rnd.next(0, 5);
    int k = 1;

    if (mode == 0) {
        k = rnd.any(powers);
        if (k > MAX_K) k = powers[powers.size() - 2];
    } else if (mode == 1) {
        int base = rnd.any(powers);
        int delta = rnd.next(-5, 5);
        k = base + delta;
    } else if (mode == 2) {
        int limit = powers[rnd.next(1, (int)powers.size() - 1)] - 1;
        k = 0;
        int bitCount = rnd.next(1, 3);
        for (int i = 0; i < bitCount; ++i) {
            int bit = 1 << rnd.next(0, 19);
            if (bit <= limit) k |= bit;
        }
    } else if (mode == 3) {
        int bits = rnd.next(1, 19);
        k = (1 << bits) - 1;
        int clearCount = rnd.next(0, min(bits, 4));
        for (int i = 0; i < clearCount; ++i) k &= ~(1 << rnd.next(0, bits - 1));
    } else if (mode == 4) {
        int hi = rnd.any(vector<int>{16, 64, 256, 1024, 4096, MAX_K});
        k = rnd.next(1, hi);
    } else {
        k = rnd.next(1, MAX_K);
    }

    k = max(1, min(MAX_K, k));
    println(k);

    return 0;
}
