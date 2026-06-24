#include "testlib.h"

using namespace std;

const double EPS = 1e-7;

double readAnswer(InStream& stream, TResult invalidVerdict, const char* streamName) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s answer", streamName);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
