#include "testlib.h"

#include <cmath>
#include <string>

using namespace std;

const long double EPS = 1e-6L;
const long long LIMIT = 1000000000LL;

long double k;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string decision = stream.readToken("[A-Z]+", "decision");
    stream.readEoln();

    if (decision == "NO") {
        stream.readEof();
        return {false};
    }

    if (decision != "YES") {
        stream.quitf(_wa, "decision must be YES or NO, found %s", decision.c_str());
    }

    long long p = stream.readLong(1, LIMIT, "p");
    long long q = stream.readLong(1, LIMIT, "q");
    stream.readEoln();
    stream.readEof();

    long double value = (long double)p / (long double)q;
    long double absError = fabsl(value - k);
    long double relError = absError / k;
    if (absError > EPS && relError > EPS) {
        stream.quitf(_wa,
                     "fraction %lld/%lld is not close enough: abs error %.12Lf, rel error %.12Lf",
                     p,
                     q,
                     absError,
                     relError);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string token = inf.readToken("0\\.[0-9]{1,8}", "k");
    k = stold(token);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid fraction while jury answered NO");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid fraction but participant answered NO");
    }

    quitf(_ok, "%s", participant.possible ? "valid fraction" : "NO");
}
