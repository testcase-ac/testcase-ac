#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

// Helper: Checks if s is a valid integer in [-10^10000, 10^10000]
bool is_valid_bigint(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-' || s[0] == '+') start = 1;
    if (start == (int)s.size()) return false; // only sign, no digits
    // No leading zeros unless single digit '0'
    if (s[start] == '0' && s.size() > start + 1) return false;
    for (int i = start; i < (int)s.size(); ++i)
        if (!isdigit(s[i])) return false;
    // Length check: max 10000 digits (not counting sign)
    if ((int)s.size() - start > 10000) return false;
    return true;
}

// Helper: Checks if s is a valid nonzero integer in [-10^10000, 10^10000] \ {0}
bool is_valid_nonzero_bigint(const string& s) {
    if (!is_valid_bigint(s)) return false;
    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    // Check not zero
    for (int i = start; i < (int)s.size(); ++i)
        if (s[i] != '0') return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A
    string A = inf.readToken("[^ ]{1,10001}", "A"); // up to 1 sign + 10000 digits
    inf.readSpace();
    string B = inf.readToken("[^ \n]{1,10001}", "B"); // up to 1 sign + 10000 digits
    inf.readEoln();

    // Check A
    ensuref(is_valid_bigint(A), "A is not a valid integer in [-10^10000, 10^10000], got: '%s'", A.c_str());
    // Check B
    ensuref(is_valid_nonzero_bigint(B), "B is not a valid nonzero integer in [-10^10000, 10^10000], got: '%s'", B.c_str());

    inf.readEof();
}
