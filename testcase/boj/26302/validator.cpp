#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 1; row <= 9; ++row) {
        inf.readLine("[1-9.]{9}", "row");
    }

    inf.readEof();
}
