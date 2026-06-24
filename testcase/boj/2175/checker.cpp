#include "testlib.h"

#include <algorithm>

using namespace std;

const double EPS = 1e-3;

struct Answer {
    double small;
    double large;
};

Answer readAnswer(InStream& stream) {
    double first = stream.readDouble();
    double second = stream.readDouble();

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after two area values");
    }
    if (first < 0 || second < 0) {
        stream.quitf(_wa, "area values must be non-negative: %.10f %.10f", first, second);
    }
    if (first > second + EPS) {
        stream.quitf(_wa, "areas are not printed in nondecreasing order: %.10f %.10f", first, second);
    }

    return {first, second};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!doubleCompare(jury.small, participant.small, EPS)) {
        quitf(_wa,
              "smaller area differs: expected %.10f, found %.10f, error %.10f",
              jury.small,
              participant.small,
              doubleDelta(jury.small, participant.small));
    }
    if (!doubleCompare(jury.large, participant.large, EPS)) {
        quitf(_wa,
              "larger area differs: expected %.10f, found %.10f, error %.10f",
              jury.large,
              participant.large,
              doubleDelta(jury.large, participant.large));
    }

    quitf(_ok, "areas %.10f %.10f are within tolerance", participant.small, participant.large);
}
