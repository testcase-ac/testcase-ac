#include "testlib.h"
#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

const long double EPS = 1e-3L;

struct Answer {
    string token;
    long double value;
};

bool isDecimalToken(const string& token) {
    int pos = 0;
    if (pos < (int)token.size() && (token[pos] == '+' || token[pos] == '-')) {
        pos++;
    }

    int integerStart = pos;
    while (pos < (int)token.size() && isdigit((unsigned char)token[pos])) {
        pos++;
    }
    if (pos == integerStart || pos >= (int)token.size() || token[pos] != '.') {
        return false;
    }

    pos++;
    int fractionalStart = pos;
    while (pos < (int)token.size() && isdigit((unsigned char)token[pos])) {
        pos++;
    }

    return pos > fractionalStart && pos == (int)token.size();
}

Answer readAnswer(InStream& stream) {
    string token = stream.readToken();
    if (!isDecimalToken(token)) {
        stream.quitf(_wa, "answer must be a decimal value, found '%s'", token.c_str());
    }

    errno = 0;
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (errno == ERANGE || end == token.c_str() || *end != '\0' || !isfinite(value)) {
        stream.quitf(_wa, "answer is not a finite real value: '%s'", token.c_str());
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    return {token, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    long double error = fabsl(participant.value - jury.value);
    if (!(error < EPS)) {
        quitf(_wa,
              "expected %s, found %s, absolute error %.12Lf is not less than %.12Lf",
              jury.token.c_str(),
              participant.token.c_str(),
              error,
              EPS);
    }

    quitf(_ok, "answer %s is within absolute tolerance", participant.token.c_str());
}
