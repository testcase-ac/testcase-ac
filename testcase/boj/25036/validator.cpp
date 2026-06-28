#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement defines no stdin. The fixed-case runner presents an
    // empty fixed input as one empty line, so accept only that representation.
    if (!inf.eof()) {
        inf.readEoln();
    }
    inf.readEof();
}
