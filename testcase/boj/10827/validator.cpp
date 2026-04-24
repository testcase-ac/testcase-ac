#include "testlib.h"
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a as a token (non-whitespace), then space, then b, then EOLN, then EOF.
    string a = inf.readToken("[^ ]+", "a");
    inf.readSpace();
    int b = inf.readInt(1, 100, "b");
    inf.readEoln();

    // Validate format of a: must contain exactly one '.', all other chars digits.
    int dot_count = 0;
    for (char c : a) {
        if (c == '.') {
            dot_count++;
        } else {
            ensuref(isdigit(c), "Invalid character in a: '%c'", c);
        }
    }
    ensuref(dot_count == 1, "a must contain exactly one decimal point, found %d", dot_count);

    // Split into integer and fractional parts
    size_t dot = a.find('.');
    string intp = a.substr(0, dot);
    string fracp = a.substr(dot + 1);

    // Both parts must be non-empty
    ensuref(!intp.empty(), "Integer part of a is empty");
    ensuref(!fracp.empty(), "Fractional part of a is empty");

    // Check fractional part length <= 9
    ensuref(fracp.size() <= 9, 
            "Fractional part has too many digits: %zu (max 9)", fracp.size());

    // Fractional part must not end with '0'
    ensuref(fracp.back() != '0', 
            "Fractional part must not end with '0', but ended with '0'");

    // Integer part: no extra leading zeros unless it's exactly "0"
    if (intp.size() > 1) {
        ensuref(intp[0] != '0', 
                "Leading zero in integer part: \"%s\"", intp.c_str());
    }

    // Integer part length <= 2 (so value <=99)
    ensuref(intp.size() <= 2, 
            "Integer part too large: \"%s\"", intp.c_str());

    // Numeric constraints: 0 < a < 100
    // We know a>0 because either intp>"0" or fracp>0 (last digit != '0')
    // Check intp < "100"
    if (intp.size() == 2) {
        // compare with "99"
        int v = (intp[0]-'0')*10 + (intp[1]-'0');
        ensuref(v < 100, "Integer part must be <100, got %d", v);
    }
    // intp.size()==1: '0'..'9' always <100

    // b was already checked by readInt
    // Done. Now ensure end of file.
    inf.readEof();
    return 0;
}
