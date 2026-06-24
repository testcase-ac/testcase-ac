#include "testlib.h"

#include <cmath>

using namespace std;

namespace {
constexpr double kTolerance = 1e-6;

double readAnswer(InStream& stream, TResult invalidResult) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "answer is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after answer");
    }
    return value;
}
}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, kTolerance)) {
        quitf(_wa,
              "expected %.17g, found %.17g, absolute/relative error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
