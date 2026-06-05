#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 0; row < 3; ++row) {
        inf.readLine("[A-Z]{3}", "board_row");
    }

    inf.readEof();
}
