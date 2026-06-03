#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000000, "strength");
        inf.readSpace();
        inf.readInt(0, 1000000, "agility");
        inf.readSpace();
        inf.readInt(0, 1000000, "intelligence");
        inf.readEoln();
    }

    inf.readEof();
}
