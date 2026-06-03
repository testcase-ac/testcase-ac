#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[A-Z]{1,20}", "candidate");
        inf.readEoln();
    }

    inf.readEof();
}
