#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[UDPC]{1,100000}", "V");
    inf.readEoln();
    inf.readEof();
}
