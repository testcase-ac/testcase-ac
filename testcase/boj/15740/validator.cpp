#include "testlib.h"
#include <string>
using namespace std;

static const int MAX_POWER = 10000;

// Validate that the string s represents an integer whose absolute value is ≤ 10^10000.
void validateBigInt(const string &s, const char *name) {
    // Must match optional '-' then 1+ digits (regex already ensured)
    bool negative = (s[0] == '-');
    const string digits = s.substr(negative ? 1 : 0);
    // There must be at least one digit
    ensuref(!digits.empty(),
            "%s: no digits found", name);
    // Check digit characters (redundant since regex enforces [0-9], but to be safe)
    for (int i = 0; i < (int)digits.size(); i++) {
        char c = digits[i];
        ensuref(c >= '0' && c <= '9',
                "%s: invalid character '%c' in digits at position %d", name, c, i);
    }
    // Numeric bound: abs(value) ≤ 10^10000
    // If length of digits > MAX_POWER+1, then > 10^10000.
    if ((int)digits.size() > MAX_POWER + 1) {
        ensuref(false,
                "%s: too many digits (%d) > %d",
                name, (int)digits.size(), MAX_POWER + 1);
    }
    // If exactly MAX_POWER+1 digits, must be ≤ "1" followed by MAX_POWER zeros.
    if ((int)digits.size() == MAX_POWER + 1) {
        // Build bound string "1" + 10000 zeros
        static string bound = string("1") + string(MAX_POWER, '0');
        // Compare lexicographically
        if (digits > bound) {
            ensuref(false,
                    "%s: absolute value exceeds 10^%d (got %s, max %s)",
                    name, MAX_POWER, digits.c_str(), bound.c_str());
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B on one line
    string A = inf.readToken("-?[0-9]+", "A");
    inf.readSpace();
    string B = inf.readToken("-?[0-9]+", "B");
    inf.readEoln();

    // Validate numeric bounds
    validateBigInt(A, "A");
    validateBigInt(B, "B");

    // End of file strictly
    inf.readEof();
    return 0;
}
