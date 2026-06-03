#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 8, "N");
    inf.readSpace();
    int m = inf.readInt(1, 25, "M");
    inf.readEoln();

    for (int mission = 0; mission < 2; ++mission) {
        for (int place = 0; place < 3; ++place) {
            if (place > 0) {
                inf.readSpace();
            }
            int progress = inf.readInt(0, 10, "progress");
            ensuref(progress % 2 == 0,
                    "progress[%d][%d] must be even: %d",
                    mission + 1,
                    place + 1,
                    progress);
        }
        inf.readEoln();
    }

    inf.readEof();
}
