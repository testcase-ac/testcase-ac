#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[ABEKMHOPCTYX]{1,100}", "word");
    inf.readEoln();
    inf.readEof();
}
