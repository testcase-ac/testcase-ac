#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    double error = fabs(participant - jury);
    if (error > EPS) {
        quitf(_wa, "expected %.10f, found %.10f, absolute error %.10f",
              jury, participant, error);
    }

    quitf(_ok, "answer %.10f is within absolute tolerance", participant);
}
