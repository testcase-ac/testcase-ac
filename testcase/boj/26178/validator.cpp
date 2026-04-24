#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

static int gcd_int(int x, int y) {
    while (y) {
        x %= y;
        std::swap(x, y);
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the fraction a/b as a single token, no extra spaces.
    string frac = inf.readToken("[0-9]+/[0-9]+", "a/b");
    inf.readEoln();

    // Split at the slash
    int slash_pos = frac.find('/');
    // Regex guarantees one slash, but double‐check for safety
    ensuref(slash_pos != (int)string::npos,
            "Invalid format: missing '/' in \"%s\"", frac.c_str());

    string sa = frac.substr(0, slash_pos);
    string sb = frac.substr(slash_pos + 1);

    // Convert to integers manually to avoid overflow and check length
    ensuref(!sa.empty(), "Missing numerator in \"%s\"", frac.c_str());
    ensuref(!sb.empty(), "Missing denominator in \"%s\"", frac.c_str());
    ensuref(sa.size() <= 4, "Numerator too long: \"%s\"", sa.c_str());
    ensuref(sb.size() <= 4, "Denominator too long: \"%s\"", sb.c_str());

    int a = 0, b = 0;
    for (char c : sa) {
        ensuref(c >= '0' && c <= '9',
                "Invalid character in numerator: '%c'", c);
        a = a * 10 + (c - '0');
    }
    for (char c : sb) {
        ensuref(c >= '0' && c <= '9',
                "Invalid character in denominator: '%c'", c);
        b = b * 10 + (c - '0');
    }

    // Check ranges 1 <= a,b <= 1000
    ensuref(1 <= a && a <= 1000,
            "Numerator out of range [1,1000]: %d", a);
    ensuref(1 <= b && b <= 1000,
            "Denominator out of range [1,1000]: %d", b);

    // Check coprimality
    ensuref(gcd_int(a, b) == 1,
            "Numerator and denominator are not coprime: %d/%d", a, b);

    inf.readEof();
    return 0;
}
