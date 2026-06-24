#include "testlib.h"

#include <array>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

array<double, 2> readAnswer(InStream& stream) {
    array<double, 2> values;
    values[0] = stream.readDouble();
    values[1] = stream.readDouble();

    for (double value : values) {
        if (!isfinite(value)) {
            stream.quitf(_wa, "answer contains non-finite value");
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after p and q");
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    array<double, 2> jury = readAnswer(ans);
    array<double, 2> participant = readAnswer(ouf);

    for (int i = 0; i < 2; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "%c differs: expected %.12f, found %.12f, error %.12f",
                  i == 0 ? 'p' : 'q',
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "p=%.12f q=%.12f", participant[0], participant[1]);
}
