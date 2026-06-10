#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long MAX_N = 1000000000000000000LL;

long long clampValue(__int128 value) {
    if (value < 1) return 1;
    if (value > MAX_N) return MAX_N;
    return static_cast<long long>(value);
}

long long fromDigits(const string& digits) {
    __int128 value = 0;
    for (char ch : digits) {
        value = value * 10 + (ch - '0');
    }
    return clampValue(value);
}

long long makeTidyNumber() {
    int len = rnd.next(1, 18);
    string digits;
    int current = rnd.next(1, 9);
    digits.push_back(char('0' + current));
    for (int i = 1; i < len; ++i) {
        current = rnd.next(current, 9);
        digits.push_back(char('0' + current));
    }
    return fromDigits(digits);
}

long long makeDropNumber() {
    int len = rnd.next(2, 18);
    string digits(len, '0');
    int pos = rnd.next(1, len - 1);

    int previous = rnd.next(1, 9);
    digits[0] = char('0' + previous);
    for (int i = 1; i < pos; ++i) {
        previous = rnd.next(previous, 9);
        digits[i] = char('0' + previous);
    }

    int dropped = rnd.next(0, previous - 1);
    digits[pos] = char('0' + dropped);
    for (int i = pos + 1; i < len; ++i) {
        digits[i] = char('0' + rnd.next(0, 9));
    }
    return fromDigits(digits);
}

long long makePowerBoundary() {
    int exp = rnd.next(1, 18);
    __int128 power = 1;
    for (int i = 0; i < exp; ++i) power *= 10;
    long long delta = rnd.next(-20LL, 20LL);
    return clampValue(power + delta);
}

long long makeRepeatedDigitNumber() {
    int len = rnd.next(1, 18);
    int digit = rnd.next(1, 9);
    string digits(len, char('0' + digit));

    if (len >= 2 && rnd.next(2)) {
        int pos = rnd.next(1, len - 1);
        digits[pos] = char('0' + rnd.next(0, digit - 1));
    }
    return fromDigits(digits);
}

long long makeRandomNumber() {
    int len = rnd.next(1, 18);
    string digits;
    digits.push_back(char('1' + rnd.next(0, 8)));
    for (int i = 1; i < len; ++i) {
        digits.push_back(char('0' + rnd.next(0, 9)));
    }
    return fromDigits(digits);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 25);
    vector<long long> values = {
        1,
        9,
        10,
        11,
        99,
        100,
        1000,
        111111111111111110LL,
        MAX_N
    };

    while ((int)values.size() < t) {
        int mode = rnd.next(5);
        if (mode == 0) {
            values.push_back(makeTidyNumber());
        } else if (mode == 1) {
            values.push_back(makeDropNumber());
        } else if (mode == 2) {
            values.push_back(makePowerBoundary());
        } else if (mode == 3) {
            values.push_back(makeRepeatedDigitNumber());
        } else {
            values.push_back(makeRandomNumber());
        }
    }

    shuffle(values.begin(), values.end());
    println(t);
    for (int i = 0; i < t; ++i) {
        println(values[i]);
    }

    return 0;
}
