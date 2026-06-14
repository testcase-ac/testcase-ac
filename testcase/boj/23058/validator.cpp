#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 8, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 1, "color");
        }
        inf.readEoln();
    }

    inf.readEof();
}
