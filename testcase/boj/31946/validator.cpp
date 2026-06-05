#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 1, "color");
        }
        inf.readEoln();
    }

    inf.readInt(1, 10, "X");
    inf.readEoln();
    inf.readEof();
}
