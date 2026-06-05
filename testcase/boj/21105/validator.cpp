#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int readFixed2Cents(int lo, int hi, const char* name) {
    string token = inf.readToken("[^ ]+", name);
    ensuref(!token.empty(), "%s must not be empty", name);

    int pos = 0;
    bool negative = false;
    if (token[pos] == '-') {
        negative = true;
        ++pos;
        ensuref(pos < (int)token.size(), "%s has a sign without digits", name);
    }

    int int_start = pos;
    while (pos < (int)token.size() && isdigit((unsigned char)token[pos])) {
        ++pos;
    }
    int int_len = pos - int_start;
    ensuref(int_len > 0, "%s is missing an integer part: %s", name, token.c_str());
    ensuref(int_len == 1 || token[int_start] != '0',
            "%s has leading zeroes in the integer part: %s", name, token.c_str());

    ensuref(pos < (int)token.size() && token[pos] == '.',
            "%s must contain a decimal point: %s", name, token.c_str());
    ++pos;
    ensuref(pos + 2 == (int)token.size(),
            "%s must have exactly two digits after the decimal point: %s",
            name, token.c_str());
    ensuref(isdigit((unsigned char)token[pos]) && isdigit((unsigned char)token[pos + 1]),
            "%s has a non-digit fractional part: %s", name, token.c_str());

    long long cents = 0;
    for (int i = int_start; i < int_start + int_len; ++i) {
        cents = cents * 10 + (token[i] - '0');
    }
    cents = cents * 100 + (token[pos] - '0') * 10 + (token[pos + 1] - '0');
    if (negative) {
        ensuref(cents != 0, "%s must not be negative zero: %s", name, token.c_str());
        cents = -cents;
    }

    ensuref(lo <= cents && cents <= hi, "%s out of range: %s", name, token.c_str());
    return (int)cents;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string p_name = "P_" + to_string(i);
        string c_name = "C_" + to_string(i);

        readFixed2Cents(100, 100000, p_name.c_str());
        inf.readSpace();
        int c = readFixed2Cents(-100000, 100000, c_name.c_str());
        // CHECK: C = -100.00 makes O = 100 * P / (C + 100) undefined, so it
        // cannot be a recoverable original price despite fitting the written bound.
        ensuref(c != -10000, "C_%d must not be -100.00", i);
        inf.readEoln();
    }

    inf.readEof();
}
