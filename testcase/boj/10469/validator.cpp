#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 0; row < 8; ++row) {
        inf.readLine("[.*]{8}", "board_row");
    }

    inf.readEof();
}
