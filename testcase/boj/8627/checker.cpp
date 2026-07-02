#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 0.001;
const double SLACK = 1e-12;

double readAnswer(InStream& stream, TResult verdict, const char* streamName) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(verdict, "%s answer is not finite", streamName);
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s answer", streamName);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    double error = fabs(participant - jury);
    if (error <= EPS + SLACK) {
        quitf(_ok, "answer %.10f is within %.10f of jury %.10f", participant, error, jury);
    }
    quitf(_wa, "expected %.10f, found %.10f, absolute error %.10f", jury, participant, error);
}
