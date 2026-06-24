#include "testlib.h"

using namespace std;

const double EPS = 1e-9;

double readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.15g, found %.15g, error %.15g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.15g is within tolerance", participant);
}
