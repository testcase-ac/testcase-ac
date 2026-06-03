#include "testlib.h"

#include <climits>
#include <string>

using namespace std;

long long readHex64(const string& name) {
    string token = inf.readToken("0x[0-9a-fA-F]{1,16}", name);
    string digits = token.substr(2);

    ensuref(digits == "0" || digits[0] != '0',
            "%s has leading zeroes: %s", name.c_str(), token.c_str());

    unsigned long long value = 0;
    for (char ch : digits) {
        int digit = 0;
        if ('0' <= ch && ch <= '9') {
            digit = ch - '0';
        } else if ('a' <= ch && ch <= 'f') {
            digit = ch - 'a' + 10;
        } else {
            digit = ch - 'A' + 10;
        }

        ensuref(value <= (static_cast<unsigned long long>(LLONG_MAX) - digit) / 16,
                "%s is outside signed 64-bit range: %s", name.c_str(), token.c_str());
        value = value * 16 + digit;
    }

    return static_cast<long long>(value);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no maximum number of ranges, so use the local testcase cap.
    const int MAX_RANGES = 100000;

    int ranges = 0;
    while (!inf.seekEof()) {
        ++ranges;
        ensuref(ranges <= MAX_RANGES, "too many input lines: %d", ranges);

        long long lo = readHex64("lo");
        inf.readSpace();
        long long hi = readHex64("hi");
        inf.readEoln();

        if (lo >= hi) {
            inf.readEof();
            return 0;
        }
    }

    ensuref(ranges > 0, "input must contain at least one range or terminating line");
    inf.readEof();
}
