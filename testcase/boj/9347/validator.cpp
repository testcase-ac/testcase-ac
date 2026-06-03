#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(5, 1000, "R");
        inf.readSpace();
        int c = inf.readInt(5, 1000, "C");
        inf.readEoln();

        bool hasPlantableSection = false;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int section = inf.readInt(0, 1, "section");
                hasPlantableSection = hasPlantableSection || section == 0;
                if (j + 1 < c) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        ensuref(hasPlantableSection, "test case %d has no plantable section", tc);
    }

    inf.readEof();
}
