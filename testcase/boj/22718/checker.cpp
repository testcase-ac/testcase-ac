#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-6;

vector<double> readAnswer(InStream& stream, int caseCount) {
    vector<double> values;
    values.reserve(caseCount);

    for (int i = 0; i < caseCount; ++i) {
        double value = stream.readDouble();
        if (!isfinite(value)) {
            stream.quitf(_wa, "answer for case %d is not finite", i + 1);
        }
        values.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", caseCount);
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int caseCount = 0;
    while (true) {
        long long k = inf.readLong();
        if (k == 0) {
            break;
        }
        ++caseCount;
    }

    vector<double> jury = readAnswer(ans, caseCount);
    vector<double> participant = readAnswer(ouf, caseCount);

    for (int i = 0; i < caseCount; ++i) {
        double error = fabs(participant[i] - jury[i]);
        if (error > EPS) {
            quitf(_wa,
                  "case %d differs from jury answer: expected %.12f, found %.12f, absolute error %.12f",
                  i + 1,
                  jury[i],
                  participant[i],
                  error);
        }
    }

    quitf(_ok, "%d answer(s) within absolute error %.1e", caseCount, EPS);
}
