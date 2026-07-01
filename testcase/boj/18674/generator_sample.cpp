#include "testlib.h"

#include <vector>

using namespace std;

using ull = unsigned long long;

const ull MAX_VALUE = 18446744073709551615ULL;

ull randomMask(int maxBit) {
    ull value = 0;
    for (int bit = 0; bit <= maxBit; ++bit) {
        if (rnd.next(2) == 1) {
            value |= (1ULL << bit);
        }
    }
    return value;
}

ull randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(0, 31);
    }
    if (mode == 1) {
        return randomMask(rnd.next(3, 15));
    }
    if (mode == 2) {
        return rnd.any(vector<ull>{0ULL, 1ULL, 2ULL, 3ULL, 7ULL, 15ULL, 255ULL, MAX_VALUE});
    }

    ull high = randomMask(rnd.next(48, 63));
    ull low = randomMask(rnd.next(0, 20));
    return high ^ low;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(6, 12);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(5);
        int A = 0;
        int B = 0;

        if (mode == 0) {
            A = 0;
            B = rnd.next(0, 12);
        } else if (mode == 1) {
            A = rnd.next(0, 12);
            B = 0;
        } else if (mode == 2) {
            A = rnd.next(1, 8);
            B = rnd.next(1, 8);
        } else if (mode == 3) {
            A = rnd.next(0, 3);
            B = rnd.next(0, 3);
        } else {
            A = rnd.next(8, 25);
            B = rnd.next(0, 25 - A);
        }

        println(A, B);

        int valueMode = rnd.next(4);
        vector<ull> values;
        for (int i = 0; i < A + B + 1; ++i) {
            values.push_back(randomValue(valueMode));
        }

        if (rnd.next(4) == 0) {
            values[rnd.next(static_cast<int>(values.size()))] = 0ULL;
        }
        if (rnd.next(4) == 0) {
            values[rnd.next(static_cast<int>(values.size()))] = MAX_VALUE;
        }

        println(values);
    }

    return 0;
}
