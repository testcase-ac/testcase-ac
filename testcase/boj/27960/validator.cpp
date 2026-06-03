#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int score_a = inf.readInt(0, 1023, "S_A");
    inf.readSpace();
    int score_b = inf.readInt(0, 1023, "S_B");
    inf.readEoln();

    inf.readEof();
}
