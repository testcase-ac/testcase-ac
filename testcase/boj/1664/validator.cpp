#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[0-9X]{19}", "pattern");
    inf.readEof();
}
