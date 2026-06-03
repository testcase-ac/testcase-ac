#include "testlib.h"

int primeExponent(long long value, int prime) {
    int exponent = 0;
    while (value % prime == 0) {
        value /= prime;
        ++exponent;
    }
    return exponent;
}

bool dividesPower(int divisor, long long base, long long exponent) {
    for (int prime = 2; prime <= divisor; ++prime) {
        int required = primeExponent(divisor, prime);
        if (required == 0) {
            continue;
        }

        long long available = 1LL * primeExponent(base, prime) * exponent;
        if (available < required) {
            return false;
        }

        while (divisor % prime == 0) {
            divisor /= prime;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 6, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000LL, "B");
    inf.readSpace();
    long long c = inf.readLong(1LL, 1000000000LL, "C");
    inf.readEoln();

    int k = inf.readInt(0, 6, "K");
    inf.readSpace();
    inf.readInt(0, 6, "L");
    inf.readEoln();

    ensuref(dividesPower(a, b, c), "B^C must be divisible by A: A=%d, B=%lld, C=%lld", a, b, c);

    inf.readEof();
}
