#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);

        // CHECK: the statement does not bound or require sequential data set numbers.
        int dataSetNumber = inf.readInt(0, 1000000000, "data_set_number");
        inf.readSpace();
        int n = inf.readInt(1, 17, "N");
        inf.readSpace();
        inf.readInt(0, n, "k");
        inf.readEoln();

        (void)dataSetNumber;
    }

    inf.readEof();
}
