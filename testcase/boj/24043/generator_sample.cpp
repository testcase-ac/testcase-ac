#include "testlib.h"

#include <vector>

using namespace std;

int randomMask(int maxBit) {
    int value = 0;
    while (value == 0) {
        for (int bit = 0; bit < maxBit; ++bit) {
            if (rnd.next(2) == 1) value ^= (1 << bit);
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = (1 << 20) - 1;
    int mode = rnd.next(5);
    vector<int> a;

    if (mode == 0) {
        a.push_back(rnd.any(vector<int>{1, 2, 3, maxValue}));
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        int poolSize = rnd.next(1, 5);
        vector<int> pool;
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, 255));
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        int n = rnd.next(2, 20);
        int maxBit = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 65) {
                a.push_back(1 << rnd.next(maxBit));
            } else {
                a.push_back(randomMask(maxBit));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 30);
        int maxBit = rnd.next(4, 20);
        for (int i = 0; i < n; ++i) a.push_back(randomMask(maxBit));
    } else {
        int n = rnd.next(2, 20);
        vector<int> pool = {maxValue, maxValue - 1, maxValue ^ (1 << rnd.next(20)), 1, 1 << rnd.next(20)};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    }

    println((int)a.size());
    println(a);

    return 0;
}
