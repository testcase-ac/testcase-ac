#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[()]{1,5000}", "S");
    inf.readEoln();
    inf.readEof();
}
