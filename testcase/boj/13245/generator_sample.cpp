#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long parseNumber(const string& s) {
    long long value = 0;
    for (char c : s) value = value * 10 + (c - '0');
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 10000000000000000LL;
    vector<long long> powers;
    for (long long p = 1; p <= maxN / 10; p *= 10) powers.push_back(p);
    powers.push_back(maxN);

    long long n = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        long long p = rnd.any(powers);
        long long delta = rnd.next(-25LL, 25LL);
        n = min(maxN, max(1LL, p + delta));
    } else if (mode == 2) {
        long long p = rnd.any(powers);
        n = rnd.next(0, 1) == 0 ? max(1LL, p - 1) : min(maxN, p + 1);
    } else if (mode == 3) {
        int len = rnd.next(1, 16);
        char digit = char('1' + rnd.next(0, 8));
        string s(len, digit);
        n = parseNumber(s);
    } else if (mode == 4) {
        int len = rnd.next(1, 16);
        string s;
        s.push_back(char('1' + rnd.next(0, 8)));
        for (int i = 1; i < len; ++i) s.push_back(char('0' + rnd.next(0, 9)));
        n = parseNumber(s);
    } else if (mode == 5) {
        long long lo = rnd.next(1LL, maxN);
        long long hi = rnd.next(lo, maxN);
        n = rnd.next(lo, hi);
    } else {
        vector<long long> edges = {
            1LL,
            9LL,
            10LL,
            11LL,
            99LL,
            100LL,
            101LL,
            999LL,
            1000LL,
            1001LL,
            9999999999999999LL,
            maxN,
        };
        n = rnd.any(edges);
    }

    println(n);
    return 0;
}
