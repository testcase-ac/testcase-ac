#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-5;
const double OUTPUT_BOUND = 1e300;

vector<double> readAnswer(InStream& stream, int n) {
    vector<double> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readDouble(-OUTPUT_BOUND,
                                      OUTPUT_BOUND,
                                      format("O_%d", i + 1));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d value(s)", n);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    vector<double> jury = readAnswer(ans, n);
    vector<double> participant = readAnswer(ouf, n);

    for (int i = 0; i < n; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "O_%d differs: expected %.12f, found %.12f, error %.12f",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "%d value(s) within tolerance", n);
}
