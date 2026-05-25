#include "testlib.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    const string BOUND = string("1") + string(100, '0');

    auto isZero = [](const string& s) {
        return s == "0";
    };

    auto validateNumber = [&](const string& s, int idx) {
        ensuref(!s.empty(), "Empty number at position %d", idx);
        int start = 0;
        if (s[0] == '-') {
            start = 1;
            ensuref((int)s.size() > 1, "Minus without digits at position %d", idx);
        }
        for (int i = start; i < (int)s.size(); i++) {
            ensuref(isdigit((unsigned char)s[i]), "Invalid character '%c' in number at position %d", s[i], idx);
        }
        int digitCount = (int)s.size() - start;
        ensuref(digitCount == 1 || s[start] != '0',
                "Leading zero in number at position %d: '%s'", idx, s.c_str());
        ensuref(!(start == 1 && s[start] == '0'),
                "Negative zero at position %d: '%s'", idx, s.c_str());

        string digits = s.substr(start);
        ensuref((int)digits.size() <= 101,
                "Absolute value has more than 101 digits at position %d: '%s'", idx, s.c_str());
        if ((int)digits.size() == 101) {
            ensuref(digits <= BOUND,
                    "Absolute value exceeds 10^100 at position %d: '%s'", idx, s.c_str());
        }
    };

    char previousOp = '\0';
    for (int i = 0; i < N; i++) {
        string tok = inf.readToken("[^]+", "number");
        validateNumber(tok, i+1);
        ensuref(previousOp != '/' || !isZero(tok),
                "Division by zero at number position %d", i + 1);
        inf.readEoln();
        if (i < N-1) {
            string op = inf.readToken("[-+*/]", "op");
            previousOp = op[0];
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
