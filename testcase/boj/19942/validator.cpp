#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 15, "N");
    inf.readEoln();

    int mp = inf.readInt(0, 500, "mp");
    inf.readSpace();
    int mf = inf.readInt(0, 500, "mf");
    inf.readSpace();
    int ms = inf.readInt(0, 500, "ms");
    inf.readSpace();
    int mv = inf.readInt(0, 500, "mv");
    inf.readEoln();
    ensuref(mp + mf + ms + mv > 0, "at least one nutrient minimum must be positive");

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 500, "p_i");
        inf.readSpace();
        inf.readInt(0, 500, "f_i");
        inf.readSpace();
        inf.readInt(0, 500, "s_i");
        inf.readSpace();
        inf.readInt(0, 500, "v_i");
        inf.readSpace();
        inf.readInt(0, 500, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
