#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isCanonicalDecimal(const string &s) {
    if (s.empty()) return false;
    // No sign allowed (ai >= 1)
    if (s[0] == '+' || s[0] == '-') return false;
    // All digits
    for (char c : s) if (!(c >= '0' && c <= '9')) return false;
    // No leading zeros unless single "0"
    if (s.size() > 1 && s[0] == '0') return false;
    return true;
}

// Compare big integer decimal string to another decimal string (both canonical, non-negative)
// returns -1 if a<b, 0 if a==b, 1 if a>b
int cmpBig(const string &a, const string &b) {
    if (a.size() != b.size())
        return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n
    int n = inf.readInt(2, 36, "n");
    inf.readEoln();

    const string MAX_A = "1" + string(100000, '0'); // 10^100000

    for (int i = 0; i < n; ++i) {
        string tok = inf.readToken("[0-9]+", "a_i");
        if (i + 1 < n) inf.readSpace(); else inf.readEoln();

        ensuref(isCanonicalDecimal(tok),
                "a_%d is not in canonical non-negative decimal form: '%s'",
                i + 1, tok.c_str());
        // range check: 1 <= ai <= 10^100000
        ensuref(!(tok.size() == 1 && tok[0] == '0'),
                "a_%d must be at least 1, found 0", i + 1);
        ensuref(cmpBig(tok, MAX_A) <= 0,
                "a_%d exceeds upper bound 10^100000", i + 1);
    }

    inf.readEof();
}
