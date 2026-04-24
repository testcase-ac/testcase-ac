#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X, A, B
    long long X = inf.readLong(1LL, 100000000000LL, "X");
    inf.readSpace();
    long long A = inf.readLong(1LL, 100000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 100000000000LL, "B");
    inf.readEoln();

    // A must be <= B
    ensuref(A <= B, "Constraint violation: A (%lld) must be <= B (%lld)", A, B);

    // Read the digits string: non-empty, only '0'..'9'
    string digits = inf.readToken("[0-9]+", "digits");
    inf.readEoln();

    // Must not exceed 10 distinct digits
    ensuref((int)digits.size() <= 10,
            "Too many digits: expected at most 10, found %d", (int)digits.size());
    // Digits must be strictly increasing (ascending, no duplicates)
    for (int i = 1; i < (int)digits.size(); i++) {
        ensuref(digits[i] > digits[i-1],
                "Digits must be in strictly increasing order without duplicates: "
                "digits[%d] = '%c' is not > digits[%d] = '%c'",
                i, digits[i], i-1, digits[i-1]);
    }

    inf.readEof();
    return 0;
}
