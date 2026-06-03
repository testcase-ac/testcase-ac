#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

const long long INT32_MAX_VALUE = 2147483647LL;

long long parsePositiveInt32(const string& s, const char* name, int caseIndex) {
    ensuref(!s.empty(), "%s is empty at dataset %d", name, caseIndex);
    ensuref(s == "0" || s[0] != '0', "%s has a leading zero at dataset %d: %s", name, caseIndex, s.c_str());

    long long value = 0;
    for (char c : s) {
        ensuref('0' <= c && c <= '9', "%s contains a non-digit at dataset %d: %s", name, caseIndex, s.c_str());
        value = value * 10 + (c - '0');
        ensuref(value <= INT32_MAX_VALUE, "%s exceeds 32-bit range at dataset %d: %s", name, caseIndex, s.c_str());
    }

    // CHECK: the bounds line says 0 <= p, q, but the input object is a
    // positive rational from the tree, so zero is not a valid numerator or
    // denominator.
    ensuref(value >= 1, "%s must be positive at dataset %d: %s", name, caseIndex, s.c_str());
    return value;
}

pair<__int128_t, __int128_t> nextFraction(long long p, long long q) {
    long long whole = p / q;
    long long remainder = p % q;

    if (remainder == 0) {
        return {1, (__int128_t)whole + 1};
    }

    __int128_t numerator = q;
    __int128_t denominator = (__int128_t)q * (whole + 1) - p;
    return {numerator, denominator};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= P; ++i) {
        setTestCase(i);

        long long K = inf.readLong(0LL, INT32_MAX_VALUE, "K");
        inf.readSpace();

        string fraction = inf.readToken("[0-9]{1,10}/[0-9]{1,10}", "p/q");
        inf.readEoln();
        size_t slash = fraction.find('/');
        ensuref(slash != string::npos && slash == fraction.rfind('/'),
                "fraction must contain exactly one slash at dataset %d: %s", i, fraction.c_str());
        long long p = parsePositiveInt32(fraction.substr(0, slash), "p", i);
        long long q = parsePositiveInt32(fraction.substr(slash + 1), "q", i);

        ensuref(__gcd(p, q) == 1, "fraction at dataset %d is not reduced: %lld/%lld", i, p, q);

        auto [nextP, nextQ] = nextFraction(p, q);
        ensuref(nextP <= INT32_MAX_VALUE && nextQ <= INT32_MAX_VALUE,
                "next fraction at dataset %d exceeds 32-bit range", i);
    }

    inf.readEof();
}
