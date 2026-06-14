#include "testlib.h"

#include <cstdlib>
#include <numeric>
#include <string>

using namespace std;

static int parseNumerator(const string& token, int slash) {
    string numerator = slash == -1 ? token : token.substr(0, slash);

    ensuref(!numerator.empty(), "empty numerator in token '%s'", token.c_str());
    ensuref(numerator[0] != '+', "positive sign is not omitted in token '%s'", token.c_str());
    ensuref(numerator != "-", "missing numerator digit in token '%s'", token.c_str());
    ensuref(numerator != "-0", "negative zero in token '%s'", token.c_str());
    ensuref(numerator == "0" || numerator == "-9" || numerator[0] != '0',
            "leading zero in token '%s'", token.c_str());
    ensuref(numerator.size() <= 2, "numerator is out of range in token '%s'", token.c_str());

    for (int i = numerator[0] == '-' ? 1 : 0; i < (int)numerator.size(); ++i) {
        ensuref('0' <= numerator[i] && numerator[i] <= '9',
                "non-digit numerator character in token '%s'", token.c_str());
    }

    int p = atoi(numerator.c_str());
    ensuref(-9 <= p && p <= 9, "numerator %d is out of range in token '%s'", p, token.c_str());
    return p;
}

static void validateRational(const string& token) {
    ensuref(!token.empty(), "empty rational token");
    int slash = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == '/') {
            ensuref(slash == -1, "multiple slashes in token '%s'", token.c_str());
            slash = i;
        }
    }

    int p = parseNumerator(token, slash);
    if (slash == -1) {
        return;
    }

    string denominator = token.substr(slash + 1);
    ensuref(!denominator.empty(), "empty denominator in token '%s'", token.c_str());
    ensuref(denominator.size() == 1 && '1' <= denominator[0] && denominator[0] <= '9',
            "denominator is out of range in token '%s'", token.c_str());

    int q = denominator[0] - '0';
    ensuref(q != 1, "denominator 1 must be omitted in token '%s'", token.c_str());
    ensuref(gcd(abs(p), q) == 1, "fraction is not reduced in token '%s'", token.c_str());
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5, "N");
    inf.readSpace();
    int m = inf.readInt(1, 5, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            string value = inf.readToken("[^ ]{1,4}", "a_ij");
            validateRational(value);
            if (j + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
