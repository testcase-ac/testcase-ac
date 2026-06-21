#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 100, "W");
    inf.readSpace();
    int h = inf.readInt(1, 100, "H");
    inf.readEoln();

    for (int board = 0; board < 2; ++board) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                inf.readInt(0, 1, board == 0 ? "initial_cell" : "target_cell");
                if (x + 1 < w) {
                    inf.readSpace();
                }
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
