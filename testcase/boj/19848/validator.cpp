#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the binary string S
    string S = inf.readToken("[01]+", "S");
    int n = (int)S.size();

    // Check length constraints
    ensuref(n >= 1 && n <= 500000,
            "Length of S is %d, but must be between 1 and 500000", n);

    // Check that the number of 0's equals the number of 1's
    long long zeros = 0;
    for (char c : S) {
        if (c == '0') zeros++;
    }
    long long ones = n - zeros;
    ensuref(zeros == ones,
            "Number of zeros (%lld) != number of ones (%lld)", zeros, ones);

    // Ensure exactly one newline after the string and then EOF
    inf.readEoln();
    inf.readEof();

    return 0;
}
