#include "testlib.h"

#include <array>

using namespace std;

const double EPS = 1e-4;

array<double, 4> readAnswer(InStream& stream) {
    array<double, 4> values;
    values[0] = stream.readDouble();
    values[1] = stream.readDouble();
    values[2] = stream.readDouble();
    values[3] = stream.readDouble();
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    array<double, 4> jury = readAnswer(ans);
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    array<double, 4> participant = readAnswer(ouf);
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    const char* names[4] = {"x_low", "y_low", "x_high", "y_high"};
    for (int i = 0; i < 4; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "%s differs: expected %.17g, found %.17g, error %.17g",
                  names[i],
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "all coordinates are within tolerance");
}
