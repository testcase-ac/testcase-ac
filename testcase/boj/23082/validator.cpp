#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input as a string to check for formatting issues (leading zeros, etc.)
    string n_str = inf.readToken("-?([0-9]{1,10})", "N");
    inf.readEoln();
    inf.readEof();

    // Check for leading zeros (except for "0" itself)
    if (n_str[0] == '-') {
        ensuref(n_str.size() == 2 || n_str[1] != '0', "Negative number with leading zeros: %s", n_str.c_str());
        ensuref(n_str.size() <= 11, "Too many digits for negative N: %s", n_str.c_str());
    } else {
        ensuref(n_str == "0" || n_str[0] != '0', "Leading zeros in N: %s", n_str.c_str());
        ensuref(n_str.size() <= 10, "Too many digits for N: %s", n_str.c_str());
    }

    // Convert to long long and check bounds
    long long N;
    try {
        size_t idx;
        N = stoll(n_str, &idx, 10);
        ensuref(idx == n_str.size(), "Invalid characters in N: %s", n_str.c_str());
    } catch (...) {
        ensuref(false, "Failed to parse N as integer: %s", n_str.c_str());
    }
    ensuref(N >= -1000000000LL && N <= 1000000000LL, "N out of bounds: %lld", N);

    return 0;
}
