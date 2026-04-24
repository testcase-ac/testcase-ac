#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: non-empty, only digits and uppercase letters
    string N = inf.readToken("[0-9A-Z]+", "N");
    inf.readSpace();
    // Read B: base between 2 and 36
    int B = inf.readInt(2, 36, "B");
    inf.readEoln();

    // Validate that each character of N is a valid digit in base B
    // and compute its decimal value
    long long val = 0;
    for (int i = 0; i < (int)N.size(); i++) {
        char c = N[i];
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            // 'A' to 'Z'
            digit = (c - 'A') + 10;
        }
        ensuref(digit < B,
                "Invalid digit '%c' at position %d for base %d", c, i, B);
        val = val * B + digit;
    }

    // Global constraint: the decimal value must be <= 1e9
    ensuref(val <= 1000000000LL,
            "Value %lld exceeds 1e9", val);

    inf.readEof();
    return 0;
}
