#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[A-Z]{1,2000000}", "s");
    inf.readEof();
}
