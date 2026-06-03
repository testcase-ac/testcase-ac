#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int w = inf.readInt(1, 1000, "W");
    inf.readEoln();

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            inf.readInt(-1, 10000, "brightness");
            if (j + 1 == w) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
