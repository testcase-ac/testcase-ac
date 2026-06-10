#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 10000, "epsilon_numerator");
    inf.readSpace();
    inf.readInt(1, 10000, "epsilon_denominator");
    inf.readEoln();

    inf.readInt(-10000, 10000, "x_coefficient");
    inf.readSpace();
    inf.readInt(-10000, 10000, "constant");
    inf.readEoln();

    inf.readInt(-10000, 10000, "x0");
    inf.readEoln();

    inf.readEof();
}
