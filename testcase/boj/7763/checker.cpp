#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-8;

double readAnswer(InStream& stream, TResult extraVerdict, const char* who) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(extraVerdict, "%s has extra output after the answer", who);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");
    double error = fabs(participant - jury);

    if (error > EPS) {
        quitf(_wa,
              "expected %.17g, found %.17g, absolute error %.17g exceeds %.17g",
              jury,
              participant,
              error,
              EPS);
    }

    quitf(_ok, "answer %.17g is within absolute error %.17g", participant, EPS);
}
