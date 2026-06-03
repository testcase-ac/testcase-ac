#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(-100, 100, "x_s");
    inf.readSpace();
    inf.readInt(-100, 100, "y_s");
    inf.readEoln();

    inf.readInt(-100, 100, "x_e");
    inf.readSpace();
    inf.readInt(-100, 100, "y_e");
    inf.readSpace();
    inf.readInt(-100, 100, "dx");
    inf.readSpace();
    inf.readInt(-100, 100, "dy");
    inf.readEoln();

    inf.readEof();
}
