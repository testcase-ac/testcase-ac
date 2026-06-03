#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long valueOf(const vector<int>& digits, int base) {
    long long value = 0;
    for (int digit : digits) value = value * base + digit;
    return value;
}

vector<long long> specialValues(int base) {
    vector<int> digits(base);
    for (int i = 0; i < base; ++i) digits[i] = i;

    vector<long long> values;
    do {
        if (digits[0] == 0) continue;
        long long value = valueOf(digits, base);
        if (value <= 1000000000LL) values.push_back(value);
    } while (next_permutation(digits.begin(), digits.end()));

    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int d = rnd.next(2, 9);
    vector<long long> values = specialValues(d);

    int mode = rnd.next(0, 5);
    long long n;
    if (mode == 0) {
        n = rnd.next(1, 1000000000);
    } else if (mode == 1 && !values.empty()) {
        long long target = rnd.any(values);
        n = max(1LL, target - rnd.next(1, 20));
    } else if (mode == 2 && !values.empty()) {
        n = rnd.any(values);
    } else if (mode == 3 && !values.empty()) {
        long long target = rnd.any(values);
        n = min(1000000000LL, target + rnd.next(1, 20));
    } else if (mode == 4 && !values.empty()) {
        n = min(1000000000LL, values.back() + rnd.next(0, 100000));
    } else {
        n = rnd.next(1, 1000);
    }

    println(n, d);
    return 0;
}
