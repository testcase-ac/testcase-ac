#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Za-z0-9]{1,100}", "A");
    inf.readEoln();
    inf.readToken("[A-Za-z0-9]{1,100}", "B");
    inf.readEoln();
    inf.readEof();
}
