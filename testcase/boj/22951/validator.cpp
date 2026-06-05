#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            inf.readInt(1, 10, "card");
            if (j < k) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
