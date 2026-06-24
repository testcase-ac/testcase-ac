#include "testlib.h"

#include <cmath>

using namespace std;

namespace {

constexpr double EPS = 0.001 + 1e-12;

struct Output {
    double value;
};

Output readCaseOutput(InStream& stream, int tc) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer[%d] is not finite", tc);
    }
    if (value < -EPS) {
        stream.quitf(_wa, "answer[%d] is negative: %.10f", tc, value);
    }
    return {value};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        Output jury = readCaseOutput(ans, tc);
        Output participant = readCaseOutput(ouf, tc);

        double error = fabs(participant.value - jury.value);
        if (error > EPS) {
            quitf(_wa,
                  "answer[%d] differs from jury by %.10f: expected %.10f, found %.10f",
                  tc,
                  error,
                  jury.value,
                  participant.value);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all answers are within absolute tolerance %.6f", EPS);
}
