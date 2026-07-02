#include "testlib.h"

#include <cmath>

using namespace std;

const long double EPS = 1e-6L;

long double readAnswer(InStream& stream) {
    long double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long double jury = readAnswer(ans);
    long double participant = readAnswer(ouf);
    long double error = fabsl(jury - participant);

    if (error >= EPS) {
        quitf(_wa,
              "expected %.17Lg, found %.17Lg, absolute error %.17Lg",
              jury,
              participant,
              error);
    }

    quitf(_ok, "answer %.17Lg is within absolute tolerance", participant);
}
