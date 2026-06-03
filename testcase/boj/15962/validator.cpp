#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    if (!inf.eof()) {
        inf.readEoln();
    }
    inf.readEof();
}
