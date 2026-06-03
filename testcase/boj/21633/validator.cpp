#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(200, 1000000000, "k");
    inf.readEoln();
    inf.readEof();
}
