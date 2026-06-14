#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(-20, 20, "f_2");
    inf.readSpace();
    inf.readInt(-20, 20, "f_1");
    inf.readSpace();
    inf.readInt(-20, 20, "f_0");
    inf.readEoln();

    inf.readInt(-20, 20, "g_1");
    inf.readSpace();
    inf.readInt(-20, 20, "g_0");
    inf.readEoln();

    inf.readEof();
}
