#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 20, "k");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        inf.readInt(1, 7, "D");
        inf.readEoln();
    }

    inf.readEof();
}
