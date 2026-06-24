#include "testlib.h"

using namespace std;

const double EPS = 1e-9;

double readAnswer(InStream& stream, TResult extraVerdict) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        quitf(extraVerdict, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
