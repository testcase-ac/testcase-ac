#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

struct Answer {
    double probability;
};

Answer readAnswer(InStream& stream, TResult invalidResult) {
    double probability = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after probability");
    }
    if (!isfinite(probability)) {
        stream.quitf(invalidResult, "probability must be finite");
    }
    if (probability < -EPS || probability > 1.0 + EPS) {
        stream.quitf(invalidResult, "probability %.12f is outside [0, 1]", probability);
    }
    return {probability};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury.probability, participant.probability, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury.probability,
              participant.probability,
              doubleDelta(jury.probability, participant.probability));
    }

    quitf(_ok, "probability %.12f is within tolerance", participant.probability);
}
