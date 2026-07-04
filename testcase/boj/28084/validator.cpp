#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000000LL, "N");
    inf.readSpace();
    inf.readInt(1, 25, "M");
    inf.readEoln();

    for (int mission = 0; mission < 2; ++mission) {
        for (int place = 0; place < 3; ++place) {
            int progress = inf.readInt(0, 10, "progress");
            ensuref(progress % 2 == 0,
                    "progress must be even at mission %d place %d: %d",
                    mission + 1, place + 1, progress);
            if (place < 2) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
