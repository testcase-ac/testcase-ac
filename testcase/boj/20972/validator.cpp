#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(0, 1000, "a_ij");
            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
