#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string formatScaled(__int128 scaled) {
    __int128 integerPart = scaled / 10;
    int fractional = (int)(scaled % 10);

    string digits;
    if (integerPart == 0) {
        digits = "0";
    } else {
        while (integerPart > 0) {
            digits.push_back(char('0' + integerPart % 10));
            integerPart /= 10;
        }
        reverse(digits.begin(), digits.end());
    }

    return digits + "." + char('0' + fractional);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const __int128 upperScaled = (__int128)10000000000000001LL * 10;
    __int128 scaled = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        scaled = rnd.next(0, 2500);
    } else if (mode == 1) {
        vector<long long> residues = {0, 5, 10, 20, 25, 40, 45, 50, 65, 70, 90};
        long long base = 90LL * rnd.next(0, 1000000);
        long long adjustment = rnd.any(residues);
        scaled = base + adjustment;
    } else if (mode == 2) {
        vector<int> impossibleFraction = {1, 2, 3, 4, 6, 7, 8, 9};
        long long integerPart = rnd.next(0, 1000000);
        scaled = (__int128)integerPart * 10 + rnd.any(impossibleFraction);
    } else if (mode == 3) {
        long long integerPart = rnd.next(9999999999999000LL, 10000000000000000LL);
        scaled = (__int128)integerPart * 10 + rnd.next(0, 9);
    } else if (mode == 4) {
        long long integerPart = rnd.next(0, 1000000);
        int fraction = rnd.next(0, 1) ? 0 : 5;
        scaled = (__int128)integerPart * 10 + fraction;
    } else {
        scaled = rnd.next(0, 1000000);
        scaled *= rnd.next(1, 1000000000);
        scaled += rnd.next(0, 9);
    }

    if (scaled < 0) scaled = 0;
    if (scaled >= upperScaled) scaled = upperScaled - 1;

    println(formatScaled(scaled));
    return 0;
}
