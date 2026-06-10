#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 10, "H");
    inf.readSpace();
    // CHECK: the prose describes an overlap width of at least 2, but the formal
    // Input bounds for this problem say 1 <= W <= 10.
    int w = inf.readInt(1, 10, "W");
    inf.readEoln();

    for (int image = 1; image <= 2; ++image) {
        for (int row = 1; row <= h; ++row) {
            for (int col = 1; col <= w; ++col) {
                inf.readInt(0, 255, image == 1 ? "B1_pixel" : "B2_pixel");
                if (col < w) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}
