#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Z]{1,100000}", "S");
    inf.readEoln();
    inf.readEof();
}
