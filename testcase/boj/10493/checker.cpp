#include "testlib.h"

using namespace std;

const double EPS = 1e-7;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCaseCount = 0;
    while (!inf.seekEof()) {
        for (int i = 0; i < 8; ++i) {
            inf.readDouble();
        }
        ++testCaseCount;
    }

    for (int tc = 1; tc <= testCaseCount; ++tc) {
        double jury = ans.readDouble();
        double participant = ouf.readDouble();

        if (!doubleCompare(jury, participant, EPS)) {
            quitf(_wa,
                  "case %d: expected %.12f, found %.12f, error %.12f",
                  tc,
                  jury,
                  participant,
                  doubleDelta(jury, participant));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "%d answer(s) within tolerance", testCaseCount);
}
