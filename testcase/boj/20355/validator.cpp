#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,100}", "w");
    inf.readEoln();
    inf.readEof();
}
