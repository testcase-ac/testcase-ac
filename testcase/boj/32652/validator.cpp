#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 50, "K");
    inf.readEoln();
    inf.readEof();
}
