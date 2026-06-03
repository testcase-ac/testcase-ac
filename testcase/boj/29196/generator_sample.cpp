#include "testlib.h"

#include <string>

using namespace std;

string randomDigits(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('0' + rnd.next(0, 9));
    }
    return s;
}

void trimTrailingZeros(string& s) {
    while (!s.empty() && s.back() == '0') {
        s.pop_back();
    }
}

string nonZeroDecimal(string digits) {
    trimTrailingZeros(digits);
    bool hasNonZero = false;
    for (char c : digits) {
        hasNonZero |= c != '0';
    }
    if (!hasNonZero) {
        digits = "1";
    }
    return "0." + digits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string digits;

    if (mode == 0) {
        digits = randomDigits(rnd.next(1, 3));
    } else if (mode == 1) {
        digits = randomDigits(8);
    } else if (mode == 2) {
        char d = char('1' + rnd.next(0, 8));
        int len = rnd.next(2, 8);
        digits.assign(len, d);
    } else if (mode == 3) {
        int len = rnd.next(2, 8);
        digits.assign(len, '0');
        digits[rnd.next(0, len - 1)] = char('1' + rnd.next(0, 8));
    } else if (mode == 4) {
        int len = rnd.next(1, 8);
        digits.assign(len, '9');
        if (len > 1 && rnd.next(0, 1)) {
            digits[rnd.next(0, len - 2)] = char('1' + rnd.next(0, 8));
        }
    } else {
        int len = rnd.next(2, 8);
        string pattern = rnd.next(0, 1) ? "142857" : "33333333";
        for (int i = 0; i < len; ++i) {
            digits += pattern[i % (int)pattern.size()];
        }
    }

    println(nonZeroDecimal(digits));
    return 0;
}
