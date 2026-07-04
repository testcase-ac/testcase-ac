#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-h][1-8]", "position");
    inf.readEoln();
    inf.readEof();
}
