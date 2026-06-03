#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomNumber(int base, int length, bool allowZero = true) {
    if (allowZero && length == 1 && rnd.next(0, 9) == 0) {
        return "0";
    }

    string d;
    d.reserve(length);
    d.push_back(char('1' + rnd.next(base - 1)));
    for (int i = 1; i < length; ++i) {
        d.push_back(char('0' + rnd.next(base)));
    }
    return d;
}

string repeatedDigitNumber(int base, int length) {
    int digit = rnd.next(1, base - 1);
    return string(length, char('0' + digit));
}

string alternatingNumber(int base, int length) {
    int a = rnd.next(1, base - 1);
    int b = rnd.next(0, base - 1);
    string d;
    d.reserve(length);
    for (int i = 0; i < length; ++i) {
        d.push_back(char('0' + (i % 2 == 0 ? a : b)));
    }
    return d;
}

string remainderTargetNumber(int base, int target, int maxLength) {
    int modulo = base - 1;
    string d;
    int sum = 0;

    while (int(d.size()) + 1 < maxLength) {
        int remaining = (target - sum + modulo) % modulo;
        if (!d.empty() && remaining < base) {
            d.push_back(char('0' + remaining));
            return d;
        }

        int digit = rnd.next(d.empty() ? 1 : 0, base - 1);
        d.push_back(char('0' + digit));
        sum = (sum + digit) % modulo;
    }

    int remaining = (target - sum + modulo) % modulo;
    if (d.empty()) {
        d.push_back(char('0' + max(1, remaining)));
    } else {
        d.push_back(char('0' + remaining));
    }
    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int base = rnd.next(2, 10);
        int mode = rnd.next(0, 6);
        int length = rnd.next(1, 60);
        string d;

        if (caseIndex == 0) {
            base = 2;
            d = "0";
        } else if (caseIndex == 1) {
            base = 10;
            d = "9";
        } else if (mode == 0) {
            d = randomNumber(base, length);
        } else if (mode == 1) {
            d = repeatedDigitNumber(base, length);
        } else if (mode == 2) {
            d = alternatingNumber(base, length);
        } else if (mode == 3) {
            d = string(length, char('0' + base - 1));
        } else if (mode == 4) {
            int target = rnd.next(0, base - 2);
            d = remainderTargetNumber(base, target, length);
        } else {
            int zeroTail = rnd.next(1, max(1, length - 1));
            d = randomNumber(base, max(1, length - zeroTail), false) + string(zeroTail, '0');
        }

        println(base, d);
    }

    return 0;
}
