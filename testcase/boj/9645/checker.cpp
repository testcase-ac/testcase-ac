#include "testlib.h"

#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

static const long double EPS = 1e-7L;

long double readProbability(InStream& stream, TResult invalidVerdict, const char* label) {
    string token = stream.readToken();
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || !isfinite(value)) {
        stream.quitf(invalidVerdict, "invalid %s token: %s", label, token.c_str());
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = 0;
    while (!inf.seekEof()) {
        int n = inf.readInt();
        inf.readInt();
        for (int i = 0; i < n; ++i) {
            inf.readToken();
        }
        ++testCount;
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        long double jury = readProbability(ans, _fail, "jury answer");
        long double participant = readProbability(ouf, _wa, "participant answer");
        long double error = fabsl(jury - participant);
        if (error > EPS) {
            quitf(_wa,
                  "case %d: expected %.17Lg, found %.17Lg, absolute error %.17Lg exceeds %.1Le",
                  caseIndex, jury, participant, error, EPS);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "%d probability value(s) within absolute error %.1Le", testCount, EPS);
}
