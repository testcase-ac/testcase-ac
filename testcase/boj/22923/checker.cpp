#include "testlib.h"

using namespace std;

const double EPS = 1e-5;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int q = inf.readInt();
    for (int i = 0; i < n; ++i) {
        inf.readInt();
        inf.readInt();
        inf.readInt();
    }
    for (int i = 0; i < q; ++i) {
        inf.readInt();
        inf.readInt();
        inf.readInt();
        inf.readInt();
    }

    for (int i = 0; i < q; ++i) {
        double jury = ans.readDouble();
        double participant = ouf.readDouble();

        if (!doubleCompare(jury, participant, EPS)) {
            quitf(_wa,
                  "line %d: expected %.15f, found %.15f, error %.15f",
                  i + 1,
                  jury,
                  participant,
                  doubleDelta(jury, participant));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d percentages are within tolerance", q);
}
