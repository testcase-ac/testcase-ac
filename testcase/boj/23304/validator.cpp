#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[a-z]{1,2000000}", "S");
    inf.readEof();
}
