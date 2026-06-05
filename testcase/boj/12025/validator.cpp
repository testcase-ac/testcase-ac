#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[0-9]{1,60}", "password");
    inf.readEoln();

    inf.readLong(1LL, 9223372036854775807LL, "k");
    inf.readEoln();

    inf.readEof();
}
