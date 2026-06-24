#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

namespace {

const double EPS = 1e-9;

struct Answer {
    vector<double> values;
};

Answer readAnswer(InStream& stream, int testCount) {
    Answer result;
    result.values.reserve(static_cast<size_t>(testCount) * 3);

    for (int tc = 1; tc <= testCount; ++tc) {
        for (int i = 0; i < 3; ++i) {
            double value = stream.readDouble();
            if (!isfinite(value)) {
                stream.quitf(_wa, "p[%d][%d] is not finite", tc, i + 1);
            }
            if (value < -EPS || value > 1.0 + EPS) {
                stream.quitf(_wa, "p[%d][%d]=%.17g is outside probability range", tc, i + 1, value);
            }
            result.values.push_back(value);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d test cases", testCount);
    }
    return result;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    Answer jury = readAnswer(ans, testCount);
    Answer participant = readAnswer(ouf, testCount);

    for (size_t i = 0; i < jury.values.size(); ++i) {
        double expected = jury.values[i];
        double found = participant.values[i];
        double error = fabs(expected - found);
        if (error > EPS) {
            quitf(_wa,
                  "value %d differs: expected %.17g, found %.17g, absolute error %.17g",
                  static_cast<int>(i + 1),
                  expected,
                  found,
                  error);
        }
    }

    quitf(_ok, "all probabilities are within absolute error %.1e", EPS);
}
