#include "testlib.h"
#include <string>
#include <cassert>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N as a token of digits
    string s = inf.readToken("[0-9]+", "N");
    // N should not start with '0'
    ensuref(s[0] != '0', "N must not start with zero, but got '%s'", s.c_str());
    // Parse into integer and check range 1 <= N < 1e9
    // We use 64-bit to avoid overflow
    int64_t N = 0;
    for (char c : s) {
        N = N * 10 + (c - '0');
        // Early overflow check: if N >= 1e9, we can break
        if (N >= 1000000000LL) break;
    }
    ensuref(N >= 1 && N < 1000000000LL,
            "N must satisfy 1 <= N < 1e9, but parsed value is %lld", N);

    inf.readEoln();
    inf.readEof();

    return 0;
}
