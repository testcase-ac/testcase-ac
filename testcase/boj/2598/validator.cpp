#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 4; ++i) {
        inf.readToken("[RGBY]{6}", format("cube_%d", i).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
