#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

struct Answer {
    bool impossible;
    double value;
};

Answer readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (doubleCompare(-1.0, value, 0.0)) {
        return {true, -1.0};
    }
    if (value < 0.0) {
        stream.quitf(_wa, "answer must be -1 or a nonnegative cost, found %.17g", value);
    }
    return {false, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "answer is -1");
        }
        quitf(_wa, "jury answer is -1, participant printed %.17g", participant.value);
    }

    if (participant.impossible) {
        quitf(_wa, "jury answer is %.17g, participant printed -1", jury.value);
    }

    if (!doubleCompare(jury.value, participant.value, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury.value,
              participant.value,
              doubleDelta(jury.value, participant.value));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant.value);
}
