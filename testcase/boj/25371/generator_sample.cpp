#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int valueOf(const vector<int>& digits, int base) {
    int value = 0;
    for (int digit : digits) value = value * base + digit;
    return value;
}

vector<int> randomDigits(int base, int maxValue) {
    vector<int> digits;
    int value = 0;
    int length = rnd.next(1, 12);
    for (int i = 0; i < length; ++i) {
        int lo = (i == 0 ? 1 : 0);
        vector<int> choices;
        for (int digit = lo; digit < base; ++digit) {
            if (value * base + digit <= maxValue) choices.push_back(digit);
        }
        if (choices.empty()) break;
        int digit = rnd.any(choices);
        digits.push_back(digit);
        value = value * base + digit;
    }
    return digits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(2, 10);
    int mode = rnd.next(0, 5);
    vector<int> digits;

    if (mode == 0) {
        int n = rnd.next(1, 1000000);
        println(n, k);
        return 0;
    }

    if (mode == 1) {
        int value = 1;
        while (value <= 1000000 / k && rnd.next(0, 1)) value *= k;
        if (rnd.next(0, 1) && value < 1000000) ++value;
        println(value, k);
        return 0;
    }

    if (mode == 2) {
        digits = randomDigits(k, 1000000);
        for (int i = 1; i < (int)digits.size(); ++i) {
            if (rnd.next(0, 99) < 45) digits[i] = 0;
        }
    } else if (mode == 3) {
        int length = rnd.next(1, 10);
        digits.push_back(rnd.next(1, k - 1));
        for (int i = 1; i < length; ++i) {
            digits.push_back(rnd.next(1, k - 1));
            if (valueOf(digits, k) > 1000000) {
                digits.pop_back();
                break;
            }
        }
    } else if (mode == 4) {
        int target = rnd.next(max(1, 1000000 - 20000), 1000000);
        println(target, k);
        return 0;
    } else {
        digits = randomDigits(k, 1000000);
        for (int i = 1; i + 1 < (int)digits.size(); i += rnd.next(1, 3)) {
            digits[i] = 0;
        }
    }

    if (digits.empty()) digits.push_back(1);
    int n = valueOf(digits, k);
    println(n, k);
    return 0;
}
