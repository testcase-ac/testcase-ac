#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        std::string kind = inf.readToken("L|G", "kind");
        inf.readSpace();
        inf.readInt(0, 1000000000, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
