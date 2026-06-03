#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        inf.readInt(1, 777, "a");
        inf.readSpace();
        inf.readInt(1, 777, "b");
        inf.readEoln();
    }

    inf.readEof();
}
