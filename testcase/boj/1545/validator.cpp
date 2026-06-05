#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,50}", "S");
    inf.readEoln();
    inf.readEof();
}
