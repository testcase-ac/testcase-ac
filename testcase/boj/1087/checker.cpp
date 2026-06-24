#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-9;
const double MAX_ANSWER = 1e100;

struct Answer {
    double value;
};

Answer readAnswer(InStream& stream) {
    double value = stream.readDouble(0.0, MAX_ANSWER, "answer");
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!doubleCompare(jury.value, participant.value, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury.value,
              participant.value,
              doubleDelta(jury.value, participant.value));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant.value);
}
