#include "testlib.h"

using long64 = long long;

const long64 LIMIT = 1000000000000LL;

long64 boundedPositive(long64 value) {
    if (value < 2) return 2;
    if (value > LIMIT) return LIMIT;
    return value;
}

long64 randomMask(int maxBit) {
    long64 value = 0;
    for (int bit = 0; bit <= maxBit; ++bit) {
        if (rnd.next(2)) value |= 1LL << bit;
    }
    return value;
}

long64 randomMaskFromAllowed(long64 allowed, int maxBit, bool nonzero) {
    long64 value = 0;
    for (int bit = 0; bit <= maxBit; ++bit) {
        long64 mask = 1LL << bit;
        if ((allowed & mask) && rnd.next(2)) value |= mask;
    }
    if (nonzero && value == 0) {
        for (int bit = 0; bit <= maxBit; ++bit) {
            long64 mask = 1LL << bit;
            if (allowed & mask) return mask;
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    long64 s = 2;
    long64 x = 2;

    if (mode == 0) {
        int maxBit = rnd.next(1, 20);
        x = randomMask(maxBit);
        long64 allowedCarryBits = ((1LL << (maxBit + 1)) - 1) & ~x;
        long64 carry = randomMaskFromAllowed(allowedCarryBits, maxBit, false);
        s = x + 2 * carry;
        if (s < 2 || x < 2) {
            x = rnd.next(2LL, 1000LL);
            s = x;
        }
    } else if (mode == 1) {
        x = rnd.next(2LL, 1000000LL);
        s = rnd.next(2LL, 1000000LL);
        if (((s - x) & 1LL) == 0) ++s;
        s = boundedPositive(s);
    } else if (mode == 2) {
        int bit = rnd.next(1, 30);
        long64 carry = 1LL << bit;
        x = carry | randomMask(bit - 1);
        s = boundedPositive(x + 2 * carry);
    } else if (mode == 3) {
        x = rnd.next(2LL, LIMIT);
        s = x;
    } else if (mode == 4) {
        x = LIMIT - rnd.next(0LL, 1000LL);
        s = LIMIT - rnd.next(0LL, 1000LL);
        if (s < 2) s = 2;
        if (x < 2) x = 2;
    } else if (mode == 5) {
        int maxBit = rnd.next(30, 38);
        x = randomMask(maxBit);
        long64 allowedCarryBits = ((1LL << (maxBit + 1)) - 1) & ~x;
        long64 carry = randomMaskFromAllowed(allowedCarryBits, maxBit, true);
        s = x + 2 * carry;
        while (s > LIMIT) {
            carry >>= 1;
            s = x + 2 * carry;
        }
        if (s < 2 || x < 2) {
            x = LIMIT;
            s = LIMIT;
        }
    } else {
        s = rnd.next(2LL, LIMIT);
        x = rnd.next(2LL, LIMIT);
    }

    println(s, x);
    return 0;
}
