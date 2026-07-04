#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        setTestCase(caseIndex);

        int jackets = inf.readInt(1, 3, "J");
        inf.readSpace();
        int pants = inf.readInt(1, 3, "P");
        inf.readSpace();
        int shirts = inf.readInt(1, 3, "S");
        inf.readSpace();
        inf.readInt(1, 10, "K");
        inf.readEoln();

        ensuref(jackets <= pants,
                "case %d: expected J <= P, got J=%d P=%d",
                caseIndex,
                jackets,
                pants);
        ensuref(pants <= shirts,
                "case %d: expected P <= S, got P=%d S=%d",
                caseIndex,
                pants,
                shirts);
    }

    inf.readEof();
}
