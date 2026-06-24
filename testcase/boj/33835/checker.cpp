#include "testlib.h"

using namespace std;

const double EPS = 1e-4;
const double MAX_ANSWER = 1e20;

double readAnswer(InStream& stream, TResult verdict, const char* name) {
    double value = stream.readDouble(0.0, MAX_ANSWER, name);
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury answer");
    double participant = readAnswer(ouf, _wa, "participant answer");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
