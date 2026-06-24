#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidResult) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, absolute error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
