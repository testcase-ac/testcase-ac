#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        inf.readInt(0, 1000000000, "K");
        inf.readEoln();

        for (int position = 1; position <= 4; ++position) {
            for (int i = 1; i <= n; ++i) {
                if (i > 1) {
                    inf.readSpace();
                }
                inf.readInt(0, 1000000000, "robot_number");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
