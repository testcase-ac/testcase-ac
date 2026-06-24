#include "testlib.h"

#include <vector>

using namespace std;

const double EPS = 1e-4;

int answerCount;

vector<double> readAnswers(InStream& stream) {
    vector<double> values(answerCount);
    for (int i = 0; i < answerCount; ++i) {
        values[i] = stream.readDouble();
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", answerCount);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inf.readInt();
    int q = inf.readInt();
    answerCount = inf.readInt();

    for (int i = 0; i < q; ++i) {
        inf.readLong();
        inf.readInt();
    }
    for (int i = 0; i < answerCount; ++i) {
        inf.readInt();
        inf.readInt();
    }

    vector<double> jury = readAnswers(ans);
    vector<double> participant = readAnswers(ouf);

    for (int i = 0; i < answerCount; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "answer[%d]: expected %.10f, found %.10f, error %.10f",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "%d answers are within tolerance", answerCount);
}
