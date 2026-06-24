#include "testlib.h"

using namespace std;

const double EPS = 1e-6;
const double MAX_COST = 1e100;

double readCost(InStream& stream, TResult invalidResult) {
    double value = stream.readDouble(0.0, MAX_COST, "minimum cost");
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after minimum cost");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readCost(ans, _fail);
    double participant = readCost(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
