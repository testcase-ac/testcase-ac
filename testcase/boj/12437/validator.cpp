#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 20, "months");
        inf.readSpace();
        inf.readInt(1, 10, "days_per_month");
        inf.readSpace();
        inf.readInt(1, 100, "days_per_week");
        inf.readEoln();
    }

    inf.readEof();
}
