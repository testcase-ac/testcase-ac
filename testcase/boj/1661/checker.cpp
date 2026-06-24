#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, const char* name) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %s", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, "jury answer");
    double participant = readAnswer(ouf, "participant answer");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
