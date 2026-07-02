#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

const long double EPS = 1e-8L;

struct Answer {
    string token;
    long double value;
};

Answer readAnswer(InStream& stream, bool participant) {
    string token = stream.readToken();
    if (!stream.seekEof()) {
        stream.quitf(participant ? _wa : _fail, "extra output after answer");
    }

    size_t exponentPos = token.find_first_of("eE");
    string mantissa = token.substr(0, exponentPos);
    size_t dotPos = mantissa.find('.');
    if (participant && dotPos != string::npos) {
        int fractionalDigits = 0;
        for (size_t i = dotPos + 1; i < mantissa.size(); ++i) {
            if (mantissa[i] >= '0' && mantissa[i] <= '9') {
                ++fractionalDigits;
            }
        }
        if (fractionalDigits > 20) {
            stream.quitf(_wa, "answer has %d digits after the decimal point", fractionalDigits);
        }
    }

    errno = 0;
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (end != token.c_str() + token.size() || errno == ERANGE || !isfinite(value)) {
        stream.quitf(participant ? _wa : _fail, "invalid real number: %s", token.c_str());
    }

    return {token, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, false);
    Answer participant = readAnswer(ouf, true);

    long double error = fabsl(jury.value - participant.value);
    if (error > EPS) {
        quitf(_wa,
              "expected %s, found %s, absolute error %.12Lf",
              jury.token.c_str(),
              participant.token.c_str(),
              error);
    }

    quitf(_ok, "answer %s is within absolute error %.1Le", participant.token.c_str(), EPS);
}
