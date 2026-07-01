#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,100}", "S1");
    inf.readEoln();
    inf.readToken("[a-z]{1,100}", "S2");
    inf.readEoln();
    inf.readEof();
}
