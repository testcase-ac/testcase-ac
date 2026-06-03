#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int minValue = -10000000;
    const int maxValue = 10000000;

    inf.readInt(minValue, maxValue, "k");
    inf.readEoln();

    int a = inf.readInt(minValue, maxValue, "a");
    inf.readSpace();
    inf.readInt(minValue, maxValue, "b");
    inf.readSpace();
    int c = inf.readInt(minValue, maxValue, "c");
    inf.readSpace();
    inf.readInt(minValue, maxValue, "d");
    inf.readEoln();

    ensuref(a != 0, "a must be nonzero");
    ensuref(c != 0, "c must be nonzero");

    inf.readEof();
}
