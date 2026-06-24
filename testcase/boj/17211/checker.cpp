#include "testlib.h"

#include <cmath>

using namespace std;

const long double EPS = 1.0L;

struct Answer {
    long double good;
    long double bad;
};

Answer readAnswer(InStream& stream) {
    Answer result;
    result.good = stream.readDouble();
    result.bad = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the two probability values");
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    long double goodError = fabsl(jury.good - participant.good);
    long double badError = fabsl(jury.bad - participant.bad);

    if (goodError > EPS || badError > EPS) {
        quitf(_wa,
              "expected %.10Lf %.10Lf, found %.10Lf %.10Lf, errors %.10Lf %.10Lf",
              jury.good, jury.bad, participant.good, participant.bad, goodError, badError);
    }

    quitf(_ok, "answers are within absolute error %.1Lf", EPS);
}
