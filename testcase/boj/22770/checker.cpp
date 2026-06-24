#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-3;
const double EPS_GUARD = 1e-12;

struct Output {
    vector<double> area;
};

Output readOutput(InStream& stream, int testCount) {
    Output output;
    output.area.reserve(testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        double value = stream.readDouble();
        if (!isfinite(value)) {
            stream.quitf(_wa, "area[%d] is not finite", tc);
        }
        if (value < 0.0) {
            stream.quitf(_wa, "area[%d] is negative: %.10f", tc, value);
        }
        output.area.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", testCount);
    }

    return output;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();

    Output jury = readOutput(ans, testCount);
    Output participant = readOutput(ouf, testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        double expected = jury.area[tc - 1];
        double found = participant.area[tc - 1];
        double error = fabs(expected - found);
        if (error > EPS + EPS_GUARD) {
            quitf(_wa,
                  "case %d: expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
                  tc,
                  expected,
                  found,
                  error,
                  EPS);
        }
    }

    quitf(_ok, "%d answers are within absolute error %.10f", testCount, EPS);
}
