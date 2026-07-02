#include "testlib.h"

#include <cmath>

using namespace std;

const long double EPS = 1e-6L;

long double readAnswer(InStream& stream, TResult verdict, const char* who) {
    string token = stream.readToken();

    size_t pos = 0;
    long double value = 0;
    try {
        value = stold(token, &pos);
    } catch (...) {
        stream.quitf(verdict, "%s answer is not a real number: '%s'", who, token.c_str());
    }
    if (pos != token.size()) {
        stream.quitf(verdict, "%s answer is not a real number: '%s'", who, token.c_str());
    }
    if (!isfinite((double)value)) {
        stream.quitf(verdict, "%s answer is not finite: '%s'", who, token.c_str());
    }
    if (value <= 0) {
        stream.quitf(verdict, "%s answer must be positive, found %.17Lg", who, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s answer", who);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long double jury = readAnswer(ans, _fail, "jury");
    long double participant = readAnswer(ouf, _wa, "participant");

    long double relativeError = fabsl(participant - jury) / fabsl(jury);
    if (relativeError > EPS) {
        quitf(_wa,
              "expected %.17Lg, found %.17Lg, relative error %.17Lg exceeds %.1Le",
              jury, participant, relativeError, EPS);
    }

    quitf(_ok, "answer %.17Lg is within relative tolerance", participant);
}
