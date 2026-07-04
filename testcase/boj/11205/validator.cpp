#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(-100000000, 100000000, "m");
    inf.readSpace();
    int l = inf.readInt(-100000000, 100000000, "l");
    inf.readEoln();

    int M = inf.readInt(-100000000, 100000000, "M");
    inf.readSpace();
    int L = inf.readInt(-100000000, 100000000, "L");
    inf.readEoln();

    int tm = inf.readInt(1, 100000000, "t_m");
    inf.readSpace();
    int tl = inf.readInt(1, 100000000, "t_l");
    inf.readEoln();

    ensuref(m != M, "Monica must move: m=%d M=%d", m, M);
    ensuref(l != L, "Lydia must move: l=%d L=%d", l, L);

    inf.readEof();
}
