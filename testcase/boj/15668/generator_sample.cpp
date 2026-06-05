#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int toInt(const vector<int>& digits) {
    int value = 0;
    for (int digit : digits) value = value * 10 + digit;
    return value;
}

int uniqueNumber(int minLen, int maxLen, vector<int>& available) {
    shuffle(available.begin(), available.end());

    int len = rnd.next(minLen, maxLen);
    vector<int> digits;
    digits.reserve(len);

    for (int digit : available) {
        if (digits.empty() && digit == 0) continue;
        digits.push_back(digit);
        if ((int)digits.size() == len) break;
    }

    vector<int> remaining;
    for (int digit : available) {
        if (find(digits.begin(), digits.end(), digit) == digits.end()) {
            remaining.push_back(digit);
        }
    }
    available = remaining;

    return toInt(digits);
}

int repeatedDigitNumber() {
    int digit = rnd.next(1, 9);
    int len = rnd.next(2, 9);
    int value = 0;
    for (int i = 0; i < len; ++i) value = value * 10 + digit;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(1, 100);
    } else if (mode == 2) {
        n = repeatedDigitNumber();
    } else if (mode == 3) {
        vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int firstLen = rnd.next(1, 5);
        int secondLen = rnd.next(1, 5);
        int a = uniqueNumber(firstLen, firstLen, digits);
        int b = uniqueNumber(secondLen, secondLen, digits);
        n = a + b;
    } else if (mode == 4) {
        vector<int> interesting = {
            10, 11, 19, 20, 99, 100, 101, 555, 98765, 123456789, 1000000000};
        n = rnd.any(interesting);
    } else {
        n = rnd.next(1, 1000000000);
    }

    println(n);
    return 0;
}
