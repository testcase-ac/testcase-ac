#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long pow10ll(int exp) {
    long long value = 1;
    for (int i = 0; i < exp; ++i) value *= 10;
    return value;
}

long long randomRepeatedDigits(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        char digit = char('0' + rnd.next(0, 9));
        if (i == 0 && len > 1 && digit == '0') digit = char('1' + rnd.next(0, 8));
        s += digit;
    }

    int repeats = rnd.next(1, max(1, len / 2));
    for (int i = 0; i < repeats; ++i) {
        int from = rnd.next(0, len - 1);
        int to = rnd.next(0, len - 1);
        s[to] = s[from];
    }

    return stoll(s);
}

long long randomDistinctDigits(int len) {
    vector<char> digits;
    for (char c = '0'; c <= '9'; ++c) digits.push_back(c);
    shuffle(digits.begin(), digits.end());

    if (len > 1 && digits[0] == '0') {
        int nonZero = rnd.next(1, 9);
        swap(digits[0], digits[nonZero]);
    }

    string s(digits.begin(), digits.begin() + len);
    return stoll(s);
}

long long randomNearBoundary() {
    int len = rnd.next(1, 12);
    long long base = pow10ll(len - 1);
    long long delta = rnd.next(0, 2000);
    if (rnd.next(0, 1) == 0) {
        return max(0LL, base - delta);
    }
    return min(1000000000000LL, base + delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(20, 60);
    vector<long long> values;

    values.push_back(0);
    values.push_back(9);
    values.push_back(10);
    values.push_back(9876543210LL);
    values.push_back(999999999999LL);
    values.push_back(1000000000000LL);

    while ((int)values.size() < n) {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            values.push_back(rnd.next(0LL, 200LL));
        } else if (mode == 1) {
            values.push_back(randomRepeatedDigits(rnd.next(1, 12)));
        } else if (mode == 2) {
            values.push_back(randomDistinctDigits(rnd.next(1, 10)));
        } else if (mode == 3) {
            values.push_back(randomNearBoundary());
        } else if (mode == 4) {
            long long center = rnd.any(vector<long long>{98, 987, 9876, 98765, 987654, 9876543, 98765432, 987654321, 9876543210LL});
            values.push_back(max(0LL, center + rnd.next(-25LL, 25LL)));
        } else {
            values.push_back(rnd.next(999999990000LL, 1000000000000LL));
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (long long value : values) {
        println(value);
    }

    return 0;
}
