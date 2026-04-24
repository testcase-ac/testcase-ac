#include "testlib.h"
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X as a token of 1 to 6 digits
    string Xs = inf.readToken("[0-9]{1,6}", "X");
    // No leading zero allowed
    ensuref(Xs[0] != '0', "X must not have leading zeros, but got \"%s\"", Xs.c_str());
    // Convert to integer and check range
    long long X = 0;
    for (char c : Xs) {
        X = X * 10 + (c - '0');
        // Keep within safe bounds
        ensuref(X <= 999999LL, "Parsed value exceeds 999999");
    }
    ensuref(X >= 1 && X <= 999999, "X must be in [1, 999999], but got %lld", X);

    // Must be end of line after X
    inf.readEoln();
    // No extra data
    inf.readEof();
    return 0;
}
