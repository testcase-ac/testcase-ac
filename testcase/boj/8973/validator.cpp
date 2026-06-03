#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    for (int row = 1; row <= 2; ++row) {
        for (int i = 1; i <= n; ++i) {
            inf.readInt(-1000, 1000, "a");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
