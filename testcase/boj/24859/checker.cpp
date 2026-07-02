#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-9;

vector<double> readAnswer(InStream& stream, int n, TResult extraOutputVerdict) {
    vector<double> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readDouble();
    }
    if (!stream.seekEof()) {
        stream.quitf(extraOutputVerdict, "extra output after %d values", n);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<double> jury = readAnswer(ans, n, _fail);
    vector<double> participant = readAnswer(ouf, n, _wa);

    for (int i = 0; i < n; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "t[%d] differs: expected %.17g, found %.17g, error %.17g",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "all %d values are within tolerance", n);
}
