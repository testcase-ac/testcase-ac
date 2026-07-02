#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 0.01;

vector<double> readOutput(InStream& stream, int testCases) {
    vector<double> values(testCases);
    for (int i = 0; i < testCases; ++i) {
        values[i] = stream.readDouble();
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answer(s)", testCases);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCases = inf.readInt();
    vector<double> jury = readOutput(ans, testCases);
    vector<double> participant = readOutput(ouf, testCases);

    for (int i = 0; i < testCases; ++i) {
        double error = fabs(participant[i] - jury[i]);
        if (error > EPS) {
            quitf(_wa,
                  "case %d: expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
                  i + 1,
                  jury[i],
                  participant[i],
                  error,
                  EPS);
        }
    }

    quitf(_ok, "%d answer(s) are within absolute error %.10f", testCases, EPS);
}
