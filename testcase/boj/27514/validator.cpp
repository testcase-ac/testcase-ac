#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1LL << 62;

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<long long> count_by_exponent(64, 0);
    bool has_nonzero = false;

    for (int i = 0; i < n; ++i) {
        long long value = inf.readLong(0LL, MAX_VALUE, "a_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }

        if (value == 0) {
            continue;
        }

        has_nonzero = true;
        ensuref((value & (value - 1)) == 0, "a_%d is not zero or a power of two: %lld", i + 1, value);

        int exponent = 0;
        while ((1LL << exponent) != value) {
            ++exponent;
        }
        ensuref(exponent <= 62, "a_%d has exponent greater than 62: %lld", i + 1, value);
        ++count_by_exponent[exponent];
    }

    ensuref(has_nonzero, "array must contain at least one power of two");

    for (int exponent = 0; exponent <= 62; ++exponent) {
        long long carry = count_by_exponent[exponent] / 2;
        count_by_exponent[exponent] %= 2;
        count_by_exponent[exponent + 1] += carry;
    }
    ensuref(count_by_exponent[63] == 0, "maximum reachable value exceeds 2^62");

    inf.readEof();
}
