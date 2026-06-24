#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inf.readInt();
    inf.readInt();
    inf.readEoln();
    inf.readEof();

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
