#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 270, "N");
    inf.readSpace();
    int k = inf.readInt(3, 1000000000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(1, k, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
