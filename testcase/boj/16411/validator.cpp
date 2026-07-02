#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-F]{8}", "start");
    inf.readEoln();
    inf.readToken("[A-F]{8}", "target");
    inf.readEoln();
    inf.readEof();
}
