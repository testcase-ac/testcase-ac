#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-6L;

long double readAnswer(InStream& stream, const char* name) {
    string token = stream.readToken("[0-9]+\\.[0-9]+", name);
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %s", name);
    }

    char* end = nullptr;
    errno = 0;
    long double value = strtold(token.c_str(), &end);
    if (errno == ERANGE || end != token.c_str() + token.size() || !isfinite(value)) {
        stream.quitf(_wa, "%s is not a finite decimal number", name);
    }
    if (value <= 0.0L) {
        stream.quitf(_wa, "%s must be positive", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long double jury = readAnswer(ans, "jury answer");
    long double participant = readAnswer(ouf, "participant answer");

    long double relativeError = fabsl(jury - participant) / jury;
    if (relativeError < EPS) {
        quitf(_ok, "relative error %.12Lf", relativeError);
    }
    quitf(_wa,
          "expected %.15Lf, found %.15Lf, relative error %.12Lf",
          jury,
          participant,
          relativeError);
}
