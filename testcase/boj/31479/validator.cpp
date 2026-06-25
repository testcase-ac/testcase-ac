#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct ParseResult {
    vector<int> exponents;
    bool hasC = false;
    bool hasD = false;
};

static bool isDigitAt(const string& s, int pos) {
    return pos < (int)s.size() && isdigit((unsigned char)s[pos]);
}

static long long parsePositiveInteger(const string& s, int& pos, long long limit, const char* field) {
    ensuref(isDigitAt(s, pos), "expected digit while reading %s at offset %d in %s", field, pos, s.c_str());
    ensuref(s[pos] != '0', "%s has leading zero or is zero at offset %d in %s", field, pos, s.c_str());

    long long value = 0;
    int start = pos;
    while (isDigitAt(s, pos)) {
        value = value * 10 + (s[pos] - '0');
        ensuref(value <= limit, "%s exceeds limit %lld in %s", field, limit, s.c_str());
        ++pos;
    }
    ensuref(pos > start, "empty integer for %s in %s", field, s.c_str());
    return value;
}

static ParseResult parsePolynomial(const string& s, bool integrated) {
    ensuref(!s.empty(), "polynomial must not be empty");

    ParseResult result;
    int pos = 0;
    int previousExponent = 501;
    int termIndex = 0;

    while (pos < (int)s.size()) {
        char sign = '+';
        if (s[pos] == '+' || s[pos] == '-') {
            sign = s[pos++];
            ensuref(termIndex > 0 || sign == '-',
                    "leading plus sign must be omitted in %s", s.c_str());
            ensuref(pos < (int)s.size(), "dangling sign at end of %s", s.c_str());
        }

        bool specialConstant = false;
        long long numerator = 1;
        long long denominator = 1;
        bool explicitCoefficient = false;
        char special = '\0';

        if (pos < (int)s.size() && (s[pos] == 'C' || s[pos] == 'D')) {
            special = s[pos++];
            specialConstant = true;
            ensuref(integrated, "m must not contain %c in %s", special, s.c_str());
            ensuref(sign == '+', "%c term must have positive sign in %s", special, s.c_str());
        } else if (isDigitAt(s, pos)) {
            explicitCoefficient = true;
            long long numeratorLimit = integrated ? 500LL : 124750000LL;
            numerator = parsePositiveInteger(s, pos, numeratorLimit, "coefficient numerator");
            if (pos < (int)s.size() && s[pos] == '/') {
                ++pos;
                denominator = parsePositiveInteger(s, pos, 500LL, "coefficient denominator");
                ensuref(denominator >= 2, "fraction denominator must be at least 2 in %s", s.c_str());
                ensuref(gcd(numerator, denominator) == 1,
                        "fraction coefficient %lld/%lld is not reduced in %s",
                        numerator, denominator, s.c_str());
            }
        }

        int exponent = 0;
        bool hasX = false;
        if (pos < (int)s.size() && s[pos] == 'x') {
            hasX = true;
            ++pos;
            exponent = 1;
            if (pos < (int)s.size() && s[pos] == '^') {
                ++pos;
                exponent = (int)parsePositiveInteger(s, pos, 500LL, "exponent");
                ensuref(exponent >= 2, "exponent 1 must omit ^ in %s", s.c_str());
            }
        }

        if (specialConstant) {
            if (special == 'C') {
                ensuref(hasX && exponent == 1, "C term must be written as Cx in %s", s.c_str());
            } else {
                ensuref(!hasX, "D term must not include x in %s", s.c_str());
                exponent = 0;
            }
            if (special == 'C') {
                ensuref(!result.hasC, "duplicate C term in %s", s.c_str());
                result.hasC = true;
            } else {
                ensuref(!result.hasD, "duplicate D term in %s", s.c_str());
                result.hasD = true;
            }
        } else {
            ensuref(hasX || explicitCoefficient,
                    "term must contain a coefficient, x, C, or D at offset %d in %s", pos, s.c_str());
            ensuref(exponent <= 500, "exponent exceeds 500 in %s", s.c_str());
            if (hasX) {
                ensuref(!explicitCoefficient || !(numerator == 1 && denominator == 1),
                        "coefficient 1 before x must be omitted in %s", s.c_str());
            }
        }

        ensuref(exponent < previousExponent,
                "exponents must be strictly decreasing in %s", s.c_str());
        previousExponent = exponent;
        result.exponents.push_back(exponent);
        ++termIndex;
    }

    if (integrated) {
        ensuref(result.hasC, "integrated expression must contain C in %s", s.c_str());
        ensuref(result.hasD, "integrated expression must contain D in %s", s.c_str());
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string integrated = inf.readToken("[^ ]{1,10000}", "i");
        inf.readSpace();
        string candidate = inf.readToken("[^ ]{1,10000}", "m");
        inf.readEoln();

        parsePolynomial(integrated, true);
        parsePolynomial(candidate, false);
    }

    inf.readEof();
}
