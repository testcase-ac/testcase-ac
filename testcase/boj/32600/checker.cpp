#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

const long double ABS_EPS = 1e-200L;
const long double REL_EPS = 1e-6L;

long double readAnswer(InStream& stream, TResult verdict, const char* who) {
    string token = stream.readToken();

    errno = 0;
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || errno == ERANGE || !isfinite(value)) {
        stream.quitf(verdict, "%s answer is not a finite floating-point number: %s",
                     who, token.c_str());
    }
    if (value < 0.0L) {
        stream.quitf(verdict, "%s answer is negative: %.20Lg", who, value);
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

    long double absoluteError = fabsl(participant - jury);
    bool accepted = absoluteError <= ABS_EPS;
    if (!accepted && jury != 0.0L) {
        accepted = absoluteError / fabsl(jury) <= REL_EPS;
    }

    if (!accepted) {
        quitf(_wa,
              "expected %.20Lg, found %.20Lg, absolute error %.20Lg",
              jury, participant, absoluteError);
    }

    quitf(_ok, "answer %.20Lg is within tolerance", participant);
}
