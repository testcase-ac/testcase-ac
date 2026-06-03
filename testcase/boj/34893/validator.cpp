#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxIngredient = 1000000000000000000LL;

    inf.readLong(0LL, kMaxIngredient, "U");
    inf.readSpace();
    inf.readLong(0LL, kMaxIngredient, "O");
    inf.readSpace();
    inf.readLong(0LL, kMaxIngredient, "S");
    inf.readEoln();
    inf.readEof();
}
