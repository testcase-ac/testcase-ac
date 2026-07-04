#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace {
constexpr long long kMaxValue = 1000000000000000000LL;

long long randomPowerScaledValue(int minExp, int maxExp) {
    int exp = rnd.next(minExp, maxExp);
    long long base = 1;
    for (int i = 0; i < exp; ++i) base *= 10;
    long long multiplier = rnd.next(1, 9);
    return min(kMaxValue, base * multiplier + rnd.next(0LL, base - 1));
}

string formatF(double value) {
    ostringstream out;
    out << setprecision(17) << value;
    return out.str();
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n;
    long long m;
    string f;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = 1;
        m = rnd.next(1LL, 1000LL);
        f = formatF(rnd.next(0.000001, 1.0));
    } else if (mode == 1) {
        n = rnd.next(2LL, 12LL);
        m = rnd.next(1LL, 1000LL);
        f = formatF(rnd.next(0.05, 1.0));
    } else if (mode == 2) {
        n = rnd.next(10LL, 100000LL);
        m = rnd.next(1000LL, 1000000000LL);
        f = formatF(rnd.next(0.0001, 1.0));
    } else if (mode == 3) {
        n = randomPowerScaledValue(12, 17);
        m = randomPowerScaledValue(12, 17);
        f = formatF(rnd.next(0.000001, 1.0));
    } else if (mode == 4) {
        n = rnd.next(2LL, kMaxValue);
        m = rnd.next(1LL, kMaxValue);
        int zeros = rnd.next(1, 17);
        f = "0." + string(zeros, '0') + to_string(rnd.next(1, 9));
    } else {
        n = rnd.next(2LL, 1000000LL);
        m = rnd.next(1LL, kMaxValue);
        f = rnd.any(vector<string>{"1", "0.5", "0.25", "0.75"});
    }

    cout << n << ' ' << m << ' ' << f << '\n';
    return 0;
}
