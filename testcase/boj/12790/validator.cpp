#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Base stats: HP, MP, ATK, DEF
        inf.readInt(1, 999, "base_HP");
        inf.readSpace();
        inf.readInt(1, 999, "base_MP");
        inf.readSpace();
        inf.readInt(1, 999, "base_ATK");
        inf.readSpace();
        inf.readInt(1, 999, "base_DEF");
        inf.readSpace();
        // Delta stats: dHP, dMP, dATK, dDEF
        inf.readInt(-999, 999, "delta_HP");
        inf.readSpace();
        inf.readInt(-999, 999, "delta_MP");
        inf.readSpace();
        inf.readInt(-999, 999, "delta_ATK");
        inf.readSpace();
        inf.readInt(-999, 999, "delta_DEF");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
