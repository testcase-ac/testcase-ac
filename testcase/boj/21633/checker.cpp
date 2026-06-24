#include "testlib.h"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

static const double EPS = 0.005 + 1e-12;

bool hasAtLeastTwoFractionDigits(const string& token) {
    size_t pos = 0;
    if (pos < token.size() && (token[pos] == '+' || token[pos] == '-')) {
        ++pos;
    }

    bool hasDigitBeforeDot = false;
    while (pos < token.size() && isdigit(token[pos])) {
        hasDigitBeforeDot = true;
        ++pos;
    }
    if (!hasDigitBeforeDot || pos == token.size() || token[pos] != '.') {
        return false;
    }
    ++pos;

    int fractionDigits = 0;
    while (pos < token.size() && isdigit(token[pos])) {
        ++fractionDigits;
        ++pos;
    }
    return fractionDigits >= 2 && pos == token.size();
}

double readCommission(InStream& stream, TResult verdict, const char* source) {
    string token = stream.readToken();
    if (!hasAtLeastTwoFractionDigits(token)) {
        stream.quitf(verdict,
                     "%s answer must be a decimal value with at least two digits after the decimal point",
                     source);
    }

    char* end = nullptr;
    double value = strtod(token.c_str(), &end);
    if (end != token.c_str() + token.size() || !isfinite(value)) {
        stream.quitf(verdict, "%s answer is not a finite decimal value", source);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readCommission(ans, _fail, "jury");
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    double participant = readCommission(ouf, _wa, "participant");
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    double error = fabs(participant - jury);
    if (error > EPS) {
        quitf(_wa, "expected %.10f, found %.10f, absolute error %.10f", jury, participant, error);
    }

    quitf(_ok, "answer %.10f is within tolerance", participant);
}
