#include "testlib.h"

#include <cmath>

using namespace std;

namespace {
const double kAbsTolerance = 0.001;

struct Answer {
    double value;
};

Answer readAnswer(InStream& stream, TResult extraOutputResult) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(extraOutputResult, "extra output after answer");
    }
    return {value};
}
}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    double error = fabs(participant.value - jury.value);
    if (error > kAbsTolerance) {
        quitf(_wa,
              "expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
              jury.value,
              participant.value,
              error,
              kAbsTolerance);
    }

    quitf(_ok,
          "answer %.10f is within absolute tolerance %.10f of jury %.10f",
          participant.value,
          kAbsTolerance,
          jury.value);
}
