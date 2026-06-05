#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInt(-100000, 100000, "a_1");
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        std::string op = inf.readToken("[*/]", "op");
        inf.readSpace();
        int value = inf.readInt(-100000, 100000, "a_i");
        ensuref(op != "/" || value != 0, "division by zero before number %d", i);
    }
    inf.readEoln();

    inf.readEof();
}
