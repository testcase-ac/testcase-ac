#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 100, "a");
        inf.readSpace();
        int b = inf.readInt(a, 100, "b");

        for (int day = a; day <= b; ++day) {
            inf.readSpace();
            inf.readInt(1, 100, "T_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
