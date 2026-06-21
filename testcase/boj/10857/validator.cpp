#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 10000, "W");
    inf.readSpace();
    int s = inf.readInt(1, 10000, "S");
    inf.readEoln();

    int x = inf.readInt(1, 100, "X");
    inf.readSpace();
    int y = inf.readInt(1, 100, "Y");
    inf.readEoln();

    for (int i = 0; i < w; ++i) {
        inf.readInts(x, 0, y, "workpiece_height");
        inf.readEoln();
    }

    for (int i = 0; i < s; ++i) {
        inf.readInts(x, 0, y, "cut_height");
        inf.readEoln();
    }

    inf.readEof();
}
