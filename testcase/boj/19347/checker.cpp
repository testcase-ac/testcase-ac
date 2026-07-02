#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-3;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int z = inf.readInt();
    double lastParticipant = 0.0;

    for (int tc = 1; tc <= z; ++tc) {
        double jury = ans.readDouble();
        double participant = ouf.readDouble();
        lastParticipant = participant;

        double error = fabs(jury - participant);
        if (error > EPS) {
            quitf(_wa,
                  "case %d: expected %.17g, found %.17g, absolute error %.17g exceeds %.17g",
                  tc,
                  jury,
                  participant,
                  error,
                  EPS);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all %d answers are within tolerance, last answer %.17g", z, lastParticipant);
}
