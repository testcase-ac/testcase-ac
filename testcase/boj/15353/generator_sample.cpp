#include "testlib.h"
#include <string>
using namespace std;

static string randomBigInt(int length) {
    string value;
    value.reserve(length);
    value.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < length; ++i) {
        value.push_back(char('0' + rnd.next(10)));
    }
    return value;
}

static string repeatedDigitBigInt(int length, char digit) {
    string value(length, digit);
    if (value[0] == '0') value[0] = char('1' + rnd.next(9));
    return value;
}

static string carryChainBigInt(int length) {
    string value(length, '9');
    if (rnd.next(2) == 0 && length > 1) {
        value[0] = char('1' + rnd.next(9));
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int lenA = 1;
    int lenB = 1;
    string a;
    string b;

    if (mode == 0) {
        a = to_string(rnd.next(1, 9999));
        b = to_string(rnd.next(1, 9999));
    } else if (mode == 1) {
        lenA = rnd.next(1, 30);
        lenB = rnd.next(1, 30);
        a = randomBigInt(lenA);
        b = randomBigInt(lenB);
    } else if (mode == 2) {
        lenA = rnd.next(2, 80);
        lenB = rnd.next(1, lenA - 1);
        if (rnd.next(2) == 0) swap(lenA, lenB);
        a = randomBigInt(lenA);
        b = randomBigInt(lenB);
    } else if (mode == 3) {
        lenA = rnd.next(1, 80);
        lenB = rnd.next(1, 80);
        a = carryChainBigInt(lenA);
        b = repeatedDigitBigInt(lenB, rnd.any(string("19")));
    } else if (mode == 4) {
        lenA = rnd.next(1, 120);
        lenB = rnd.next(1, 120);
        a = repeatedDigitBigInt(lenA, rnd.any(string("123456789")));
        b = repeatedDigitBigInt(lenB, rnd.any(string("123456789")));
    } else {
        lenA = rnd.next(9000, 10000);
        lenB = rnd.next(9000, 10000);
        a = randomBigInt(lenA);
        b = randomBigInt(lenB);
    }

    println(a, b);
    return 0;
}
