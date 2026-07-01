#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says n < 1000, but a 4 x n rectangle with 2n
    // dominoes implies a positive width.
    inf.readInt(1, 999, "n");
    inf.readEoln();
    inf.readEof();
}
