#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

long long readTimeScaled() {
    // CHECK: Samples show non-fixed fractional width, so accept canonical real tokens
    // with either no decimal point or 1 to 4 fractional digits.
    string token = inf.readToken("[0-9][0-9.]{0,14}", "T");

    size_t dot = token.find('.');
    ensuref(dot == string::npos || token.find('.', dot + 1) == string::npos,
            "T has multiple decimal points: %s", token.c_str());

    string integerPart = dot == string::npos ? token : token.substr(0, dot);
    string fractionalPart = dot == string::npos ? string() : token.substr(dot + 1);

    ensuref(!integerPart.empty(), "T has empty integer part: %s", token.c_str());
    ensuref(integerPart == "0" || integerPart[0] != '0',
            "T has leading zero: %s", token.c_str());
    for (char ch : integerPart) {
        ensuref('0' <= ch && ch <= '9', "T has invalid integer digit: %s", token.c_str());
    }

    if (dot != string::npos) {
        ensuref(!fractionalPart.empty(), "T has empty fractional part: %s", token.c_str());
        ensuref(fractionalPart.size() <= 4,
                "T has more than four fractional digits: %s", token.c_str());
        for (char ch : fractionalPart) {
            ensuref('0' <= ch && ch <= '9',
                    "T has invalid fractional digit: %s", token.c_str());
        }
    }

    long long integerValue = 0;
    for (char ch : integerPart) {
        integerValue = integerValue * 10 + (ch - '0');
        ensuref(integerValue <= 1000000000LL, "T is too large: %s", token.c_str());
    }

    long long fractionalValue = 0;
    for (char ch : fractionalPart) {
        fractionalValue = fractionalValue * 10 + (ch - '0');
    }
    for (size_t i = fractionalPart.size(); i < 4; ++i) {
        fractionalValue *= 10;
    }

    ensuref(integerValue >= 1LL, "T is less than 1: %s", token.c_str());
    ensuref(integerValue < 1000000000LL || fractionalValue == 0LL,
            "T is greater than 1000000000: %s", token.c_str());

    return integerValue * 10000LL + fractionalValue;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    readTimeScaled();
    inf.readEoln();

    vector<long long> x = inf.readLongs(n, 1LL, 1000000000LL, "x_i");
    inf.readEoln();

    vector<long long> v = inf.readLongs(n, 1LL, 1000000000LL, "v_i");
    inf.readEoln();

    inf.readEof();
}
