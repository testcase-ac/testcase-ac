#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100, "P");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        int n = inf.readInt(1, 1000, "N");
        for (int j = 1; j <= n; ++j) {
            inf.readSpace();
            inf.readInt(1, 10, "c");
        }
        inf.readEoln();
    }

    inf.readEof();
}
