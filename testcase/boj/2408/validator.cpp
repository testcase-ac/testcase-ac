#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // Prepare the bound string "10^100" = "1" followed by 100 zeros
    const string BOUND = string("1") + string(100, '0');

    auto validateNumber = [&](const string &s, int idx) {
        // s must match -?[0-9]+
        ensuref(!s.empty(), "Empty number at position %d", idx);
        int start = 0;
        if (s[0] == '-') {
            start = 1;
            ensuref((int)s.size() > 1, "Minus without digits at position %d", idx);
        }
        for (int i = start; i < (int)s.size(); i++) {
            ensuref(isdigit(s[i]), "Invalid character '%c' in number at position %d", s[i], idx);
        }
        // remove leading zeros for absolute value check
        int p = start;
        while (p < (int)s.size() && s[p] == '0') p++;
        string digits;
        if (p >= (int)s.size()) {
            // the value is zero
            digits = "0";
        } else {
            digits = s.substr(p);
        }
        // check length of digits <= 101
        ensuref((int)digits.size() <= 101,
                "Absolute value has more than 101 digits at position %d: '%s'", idx, s.c_str());
        if ((int)digits.size() == 101) {
            // must be <= "1" + 100 zeros
            ensuref(digits <= BOUND,
                    "Absolute value exceeds 10^100 at position %d: '%s'", idx, s.c_str());
        }
    };

    // Read the sequence: number, ( operator, number )*
    for (int i = 0; i < N; i++) {
        // Read a number line
        string tok = inf.readToken("[^]+", "number");
        validateNumber(tok, i+1);
        inf.readEoln();
        // After each number except the last, read an operator line
        if (i < N-1) {
            // operator must be one of + - * /
            inf.readToken("[-+*/]", "op");
            inf.readEoln();
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
