#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[a-z]{1,100000}", "S");
    inf.readInt(1, 100000, "K");
    inf.readEoln();
    inf.readEof();
    return 0;
}
