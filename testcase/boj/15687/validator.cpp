#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    ensuref(inf.seekEof(), "expected no input tokens");
    inf.readEof();
}
