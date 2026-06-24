#include "testlib.h"
#include <cerrno>
#include <cstdlib>
#include <cmath>

using namespace std;

const double ABS_EPS = 1e-6;
const double REL_EPS = 1e-9;

double readAnswer(InStream& stream) {
    string token = stream.readToken();
    char* end = nullptr;
    errno = 0;
    double value = strtod(token.c_str(), &end);
    TResult invalidVerdict = (&stream == &ans ? _fail : _wa);
    if (errno == ERANGE || end != token.c_str() + token.size() || !isfinite(value)) {
        stream.quitf(invalidVerdict, "payout must be a finite floating-point value");
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after payout");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    double absoluteError = fabs(participant - jury);
    double relativeError = absoluteError / max(1.0, fabs(jury));
    if (absoluteError <= ABS_EPS || relativeError <= REL_EPS) {
        quitf(_ok, "answer %.12f is within tolerance of %.12f", participant, jury);
    }

    quitf(_wa,
          "expected %.12f, found %.12f, absolute error %.12g, relative error %.12g",
          jury,
          participant,
          absoluteError,
          relativeError);
}
