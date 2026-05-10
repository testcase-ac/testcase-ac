#include "testlib.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N numbers on the next line
    for (int i = 1; i <= N; i++) {
        // Read the token: one or more digits
        string s = inf.readToken("[0-9]+", "num");
        if (i < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
        // Check that if it's more than one digit, it does not start with '0'
        // Single "0" is allowed, multi-digit starting with '0' is not.
        ensuref(s == "0" || s[0] != '0',
                "Leading zero detected in number at position %d: \"%s\"", i, s.c_str());
        // Parse and check range [0, 1e9]
        // stoll is safe here because s matches [0-9]+
        long long x = atoll(s.c_str());
        ensuref(0 <= x && x <= 1000000000LL,
                "Number out of allowed range at position %d: %lld", i, x);
    }

    // No extra data
    inf.readEof();
    return 0;
}
