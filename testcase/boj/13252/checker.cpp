#include "testlib.h"

using namespace std;

static const double EPS = 1e-3;

struct Answer {
    double value;
};

Answer readAnswer(InStream& stream) {
    double value = stream.readDouble();
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
              "expected %.12f, found %.12f, error %.12f",
              jury.value,
              participant.value,
              doubleDelta(jury.value, participant.value));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant.value);
}
