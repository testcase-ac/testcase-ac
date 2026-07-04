#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(2, 400, "H");
    inf.readSpace();
    int w = inf.readInt(2, 400, "W");
    inf.readEoln();

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            inf.readInt(0, 2, "color");
            if (j + 1 == w) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
