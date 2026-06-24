#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-6;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        inf.readToken();
    }
    for (int i = 0; i < n - 1; ++i) {
        inf.readInt();
        inf.readInt();
    }
    int q = inf.readInt();

    const int outputCount = q + 1;
    const double maxExpected = 2.0 * n;

    vector<double> jury(outputCount);
    for (int i = 0; i < outputCount; ++i) {
        jury[i] = ans.readDouble(0.0, maxExpected, format("jury answer[%d]", i + 1).c_str());
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer sequence");
    }

    vector<double> participant(outputCount);
    for (int i = 0; i < outputCount; ++i) {
        participant[i] = ouf.readDouble(0.0, maxExpected, format("participant answer[%d]", i + 1).c_str());
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer sequence");
    }

    for (int i = 0; i < outputCount; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "answer[%d] differs: expected %.17g, found %.17g, error %.17g",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "%d answers are within tolerance", outputCount);
}
