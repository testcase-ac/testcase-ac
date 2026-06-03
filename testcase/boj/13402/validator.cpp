#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-z]{1,4000}", "s_1");
    inf.readEoln();
    inf.readToken("[a-z]{1,4000}", "s_2");
    inf.readEoln();
    inf.readEof();
}
