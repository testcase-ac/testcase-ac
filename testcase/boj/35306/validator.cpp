#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 2000, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            inf.readInt(1, 200000, "score");
            if (j + 1 < k) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
