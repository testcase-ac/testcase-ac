#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int count = 0;
    while (true) {
        int m = inf.readInt(0, 1000000000, "m");
        inf.readEoln();

        if (m == 0) {
            break;
        }

        ++count;
        ensuref(count <= 100, "number of data values exceeds 100");
    }

    inf.readEof();
}
