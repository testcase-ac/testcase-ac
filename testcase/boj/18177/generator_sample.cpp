#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_CODE = (1 << 30) - 1;

int randomMask(int minBits, int maxBits) {
    int bitCount = rnd.next(minBits, maxBits);
    vector<int> bits;
    for (int bit = 0; bit < 30; ++bit) bits.push_back(bit);
    shuffle(bits.begin(), bits.end());

    int mask = 0;
    for (int i = 0; i < bitCount; ++i) mask |= (1 << bits[i]);
    return mask;
}

int withNoise(int base, int noiseBits) {
    int mask = base;
    for (int i = 0; i < noiseBits; ++i) {
        int bit = rnd.next(0, 29);
        if (rnd.next(0, 1)) {
            mask |= (1 << bit);
        } else if ((mask & ~(1 << bit)) != 0) {
            mask &= ~(1 << bit);
        }
    }
    return max(mask, 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    vector<int> schedule;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) schedule.push_back(1 << rnd.next(0, 29));
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        k = n;
        for (int i = 0; i < n; ++i) schedule.push_back(randomMask(1, 8));
    } else if (mode == 2) {
        n = rnd.next(5, 35);
        k = rnd.next(2, min(n, 12));
        int common = randomMask(1, 5);
        for (int i = 0; i < n; ++i) schedule.push_back(withNoise(common, rnd.next(0, 8)));
    } else if (mode == 3) {
        n = rnd.next(6, 45);
        k = rnd.next(1, n);
        vector<int> anchors = {1, 1 << 29, MAX_CODE, (1 << 29) | 1, (1 << 15) - 1};
        for (int i = 0; i < n; ++i) schedule.push_back(withNoise(rnd.any(anchors), rnd.next(0, 5)));
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        k = rnd.next(max(1, n / 3), n);
        for (int i = 0; i < n; ++i) schedule.push_back(randomMask(10, 30));
    } else {
        n = rnd.next(1, 60);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) schedule.push_back(rnd.next(1, MAX_CODE));
    }

    shuffle(schedule.begin(), schedule.end());

    println(n, k);
    println(schedule);

    return 0;
}
