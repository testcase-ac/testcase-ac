#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string digitsOfLength(int len, bool allowLeadingZero) {
    string s;
    s.reserve(len);
    if (allowLeadingZero) {
        s.push_back(char('0' + rnd.next(0, 9)));
    } else {
        s.push_back(char('1' + rnd.next(0, 8)));
    }
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(0, 9)));
    }
    return s;
}

string repeatedDigits(int len, char digit) {
    return string(len, digit);
}

string alternatingDigits(int len, char a, char b) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(i % 2 == 0 ? a : b);
    }
    return s;
}

string signedNumber(string digits, int signMode) {
    if (signMode == 0) return digits;
    return "-" + digits;
}

int compactLength() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 6);
    if (mode == 2) return rnd.next(7, 20);
    if (mode == 3) return rnd.next(21, 80);
    return rnd.next(81, 200);
}

string arbitraryNumber() {
    int len = compactLength();
    bool leadingZero = rnd.next(0, 4) == 0;
    return signedNumber(digitsOfLength(len, leadingZero), rnd.next(0, 1));
}

pair<string, string> tinyCase() {
    vector<string> values = {"0", "-0", "1", "-1", "2", "-2", "9", "-9", "10", "-10"};
    return {rnd.any(values), rnd.any(values)};
}

pair<string, string> leadingZeroCase() {
    int lenA = rnd.next(2, 30);
    int lenB = rnd.next(2, 30);
    string a = repeatedDigits(rnd.next(1, min(6, lenA - 1)), '0') + digitsOfLength(lenA - 1, true);
    string b = repeatedDigits(rnd.next(1, min(6, lenB - 1)), '0') + digitsOfLength(lenB - 1, true);
    return {signedNumber(a, rnd.next(0, 1)), signedNumber(b, rnd.next(0, 1))};
}

pair<string, string> carryBorrowCase() {
    int len = rnd.next(2, 80);
    string a;
    string b;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        a = repeatedDigits(len, '9');
        b = "1";
    } else if (mode == 1) {
        a = "1" + repeatedDigits(len - 1, '0');
        b = "1";
    } else {
        a = alternatingDigits(len, '9', '0');
        b = alternatingDigits(len, '1', '9');
    }
    return {signedNumber(a, rnd.next(0, 1)), signedNumber(b, rnd.next(0, 1))};
}

pair<string, string> differentLengthCase() {
    int shortLen = rnd.next(1, 8);
    int longLen = rnd.next(40, 250);
    string a = signedNumber(digitsOfLength(shortLen, rnd.next(0, 5) == 0), rnd.next(0, 1));
    string b = signedNumber(digitsOfLength(longLen, rnd.next(0, 6) == 0), rnd.next(0, 1));
    if (rnd.next(0, 1)) swap(a, b);
    return {a, b};
}

pair<string, string> nearLimitCase() {
    int lenA = rnd.next(300, 1000);
    int lenB = rnd.next(300, 1000);
    string a = rnd.next(0, 1) ? repeatedDigits(lenA, '9') : digitsOfLength(lenA, false);
    string b = rnd.next(0, 1) ? repeatedDigits(lenB, '9') : digitsOfLength(lenB, false);
    return {signedNumber(a, rnd.next(0, 1)), signedNumber(b, rnd.next(0, 1))};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    pair<string, string> input;
    int mode = rnd.next(0, 5);
    if (mode == 0) input = tinyCase();
    else if (mode == 1) input = leadingZeroCase();
    else if (mode == 2) input = carryBorrowCase();
    else if (mode == 3) input = differentLengthCase();
    else if (mode == 4) input = nearLimitCase();
    else input = {arbitraryNumber(), arbitraryNumber()};

    println(input.first);
    println(input.second);
    return 0;
}
