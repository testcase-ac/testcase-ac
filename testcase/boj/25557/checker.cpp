#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-7;

vector<double> readAnswers(InStream& stream, int n) {
    vector<double> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readDouble();
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    vector<double> jury = readAnswers(ans, n);
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }

    vector<double> participant = readAnswers(ouf, n);
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    for (int i = 0; i < n; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "answer[%d] expected %.12f, found %.12f, error %.12f",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "all %d answers are within tolerance", n);
}
