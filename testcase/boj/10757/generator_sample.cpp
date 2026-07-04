#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string randomNumber(int len) {
    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

string repeatedDigitNumber(int len, char digit) {
    string s(len, digit);
    if (s[0] == '0') {
        s[0] = '1';
    }
    return s;
}

string patternedNumber(int len, const string& pattern) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(pattern[i % int(pattern.size())]);
    }
    if (s[0] == '0') {
        s[0] = char('1' + rnd.next(9));
    }
    return s;
}

pair<string, string> makeCase(int mode) {
    if (mode == 0) {
        return {randomNumber(rnd.next(1, 3)), randomNumber(rnd.next(1, 3))};
    }

    if (mode == 1) {
        int len = rnd.next(8, 30);
        return {repeatedDigitNumber(len, '9'), randomNumber(rnd.next(1, len))};
    }

    if (mode == 2) {
        int aLen = rnd.next(1, 20);
        int bLen = rnd.next(aLen, 60);
        return {randomNumber(aLen), randomNumber(bLen)};
    }

    if (mode == 3) {
        int len = rnd.next(15, 80);
        return {patternedNumber(len, "9090"), patternedNumber(len, "1010")};
    }

    int len = rnd.next(120, 500);
    string a = randomNumber(len);
    string b = randomNumber(len);
    for (int i = len - 1; i >= max(0, len - rnd.next(20, 80)); --i) {
        a[i] = char('5' + rnd.next(5));
        b[i] = char('5' + rnd.next(5));
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    auto [a, b] = makeCase(mode);
    println(a, b);

    return 0;
}
