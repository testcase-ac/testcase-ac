#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[a-h][1-8]", "start");
    inf.readEoln();
    inf.readToken("[a-h][1-8]", "finish");
    inf.readEoln();
    inf.readEof();
}
