#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int length = 0;
    while (!inf.eof()) {
        unsigned char c = static_cast<unsigned char>(inf.readChar());
        ensuref(c <= 127, "character %d has ASCII code %d", length + 1, c);
        ++length;
        ensuref(length <= 50000, "input has more than 50000 characters");
    }

    ensuref(length >= 10000, "input has fewer than 10000 characters: %d", length);
    inf.readEof();
}
