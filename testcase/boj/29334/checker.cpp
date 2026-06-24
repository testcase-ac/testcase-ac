#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-6;

vector<double> readAnswer(InStream& stream, int n) {
    vector<double> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readDouble();
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    vector<double> jury = readAnswer(ans, n);
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    vector<double> participant = readAnswer(ouf, n);
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    for (int i = 0; i < n; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "p[%d] differs: expected %.15g, found %.15g, delta %.15g",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "all %d probabilities are within tolerance", n);
}
