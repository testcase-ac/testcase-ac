#include "testlib.h"

#include <cmath>
#include <string>

using namespace std;

const double EPS = 1e-9;

struct Answer {
    double icpc;
    double acm;
};

Answer readAnswer(InStream& stream) {
    Answer result;
    result.icpc = stream.readDouble();
    result.acm = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after two probabilities");
    }
    return result;
}

void checkClose(double expected, double actual, const string& name) {
    double error = fabs(expected - actual);
    if (error > EPS) {
        quitf(_wa,
              "%s probability differs: expected %.17g, found %.17g, absolute error %.17g",
              name.c_str(), expected, actual, error);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    checkClose(jury.icpc, participant.icpc, "ICPC-card");
    checkClose(jury.acm, participant.acm, "ACM-card");

    quitf(_ok, "both probabilities are within absolute error %.1e", EPS);
}
