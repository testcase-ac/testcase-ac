#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int caseIndex = 1;; ++caseIndex) {
        int c = inf.readInt(0, 32, "c");
        inf.readSpace();
        int s = inf.readInt(0, 32, "s");
        inf.readEoln();

        if (c == 0 && s == 0) {
            break;
        }

        ensuref(c > 0, "c must be positive before terminator at case %d", caseIndex);
        ensuref(s > 0, "s must be positive before terminator at case %d", caseIndex);
        ensuref(c * s <= 32, "c * s exceeds 32 at case %d: %d * %d", caseIndex, c, s);
    }

    inf.readEof();
}
