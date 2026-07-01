#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 1;
    while (true) {
        int n = inf.readInt(0, 50000, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(dataset++);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
