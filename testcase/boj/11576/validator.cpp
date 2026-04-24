#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read bases A and B
    int A = inf.readInt(2, 30, "A");
    inf.readSpace();
    int B = inf.readInt(2, 30, "B");
    inf.readEoln();

    // Read the number of digits m
    int m = inf.readInt(1, 25, "m");
    inf.readEoln();

    // Read the digits in base A
    vector<int> digits = inf.readInts(m, 0, A - 1, "digit");
    inf.readEoln();

    // Leading digit must be non-zero (number is positive)
    ensuref(digits[0] != 0,
        "Leading zero detected: digit[0] = 0");

    // Compute the decimal value and check bounds (< 2^20, > 0)
    const long long LIMIT = (1LL << 20);
    long long value = 0;
    for (int d : digits) {
        value = value * A + d;
    }
    ensuref(value > 0,
        "Decimal value must be positive but got %lld", value);
    ensuref(value < LIMIT,
        "Decimal value %lld is not less than 2^20 (%lld)", value, LIMIT);

    inf.readEof();
    return 0;
}
