#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Z]{1,100}", "encrypted");
    inf.readEoln();
    inf.readEof();
}
