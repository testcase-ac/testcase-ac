#include "testlib.h"

#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

bool isCanonicalUnsignedIntegerPart(const string& s, int l, int r) {
    if (l >= r) return false;
    if (s[l] == '0') return l + 1 == r;
    if (s[l] < '1' || s[l] > '9') return false;
    for (int i = l + 1; i < r; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

bool isCanonicalRealToken(const string& s) {
    if (s.empty()) return false;

    int pos = 0;
    if (s[pos] == '-') {
        ++pos;
        if (pos == (int)s.size()) return false;
    }

    int exponentPos = -1;
    for (int i = pos; i < (int)s.size(); ++i) {
        if (s[i] == 'e' || s[i] == 'E') {
            if (exponentPos != -1) return false;
            exponentPos = i;
        }
    }

    int mantissaEnd = exponentPos == -1 ? (int)s.size() : exponentPos;
    int dotPos = -1;
    for (int i = pos; i < mantissaEnd; ++i) {
        if (s[i] == '.') {
            if (dotPos != -1) return false;
            dotPos = i;
        }
    }

    int integerEnd = dotPos == -1 ? mantissaEnd : dotPos;
    if (!isCanonicalUnsignedIntegerPart(s, pos, integerEnd)) return false;

    if (dotPos != -1) {
        if (dotPos + 1 == mantissaEnd) return false;
        for (int i = dotPos + 1; i < mantissaEnd; ++i) {
            if (s[i] < '0' || s[i] > '9') return false;
        }
    }

    if (exponentPos != -1) {
        int expStart = exponentPos + 1;
        if (expStart == (int)s.size()) return false;
        if (s[expStart] == '-') {
            ++expStart;
            if (expStart == (int)s.size()) return false;
        }
        if (!isCanonicalUnsignedIntegerPart(s, expStart, (int)s.size())) return false;
    }

    return true;
}

long double parseReal(const string& token, const char* name) {
    // CHECK: cap real-token spelling length to keep validation work bounded while accepting ordinary decimal and exponent forms.
    ensuref(token.size() <= 256, "%s is too long", name);
    ensuref(isCanonicalRealToken(token), "%s is not a canonical real token: %s", name, token.c_str());

    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    ensuref(end != nullptr && *end == '\0', "%s cannot be parsed: %s", name, token.c_str());
    ensuref(isfinite(value), "%s is not finite: %s", name, token.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    const long double maxAbsCoefficient = 5.2e22L;
    for (int i = 1; i <= n + 1; ++i) {
        string coefficient = inf.readToken("[^ \n\r\t]+", "a_i");
        long double value = parseReal(coefficient, "a_i");
        ensuref(fabsl(value) <= maxAbsCoefficient, "a_%d is outside the allowed absolute bound", i);
        if (i <= n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    int k = inf.readInt(2, 10000000, "k");
    ensuref(k % 2 == 0, "k must be even");
    inf.readEoln();
    inf.readEof();
}
