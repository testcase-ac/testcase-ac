#include "testlib.h"

#include <numeric>

using namespace std;

namespace {

constexpr long long MAX_PRIME = 20000000LL;
constexpr long long MAX_C = MAX_PRIME * MAX_PRIME;

bool isPrime(long long value) {
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (long long divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

void validateSharedPrimePair(long long left, long long right, const char* leftName,
                             const char* rightName, const char* sharedName) {
    long long shared = gcd(left, right);
    ensuref(shared <= MAX_PRIME && isPrime(shared),
            "%s and %s must share prime %s, got gcd %lld", leftName, rightName,
            sharedName, shared);

    long long leftOther = left / shared;
    long long rightOther = right / shared;
    ensuref(leftOther <= MAX_PRIME && isPrime(leftOther),
            "%s / %s must be prime at most %lld, got %lld", leftName, sharedName,
            MAX_PRIME, leftOther);
    ensuref(rightOther <= MAX_PRIME && isPrime(rightOther),
            "%s / %s must be prime at most %lld, got %lld", rightName, sharedName,
            MAX_PRIME, rightOther);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long c1 = inf.readLong(1LL, MAX_C, "c_1");
    inf.readSpace();
    long long c2 = inf.readLong(1LL, MAX_C, "c_2");
    inf.readSpace();
    long long c3 = inf.readLong(1LL, MAX_C, "c_3");
    inf.readSpace();
    long long c4 = inf.readLong(1LL, MAX_C, "c_4");
    inf.readSpace();
    long long c5 = inf.readLong(1LL, MAX_C, "c_5");
    inf.readSpace();
    long long c6 = inf.readLong(1LL, MAX_C, "c_6");
    inf.readEoln();
    inf.readEof();

    ensuref(c1 != c5, "c_1 and c_5 must be different");
    ensuref(c3 != c6, "c_3 and c_6 must be different");

    validateSharedPrimePair(c1, c5, "c_1", "c_5", "x_2");
    validateSharedPrimePair(c3, c6, "c_3", "c_6", "x_6");

    (void)c2;
    (void)c4;
}
