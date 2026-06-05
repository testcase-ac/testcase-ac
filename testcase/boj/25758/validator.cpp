#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readToken("[A-Z]{2}", "gene");
    }
    inf.readEoln();

    inf.readEof();
}
