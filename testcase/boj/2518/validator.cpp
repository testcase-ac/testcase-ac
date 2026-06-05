#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 300000, "N");
    inf.readEoln();
    ensuref(n % 3 == 0, "N must be divisible by 3: %d", n);

    for (int person = 1; person <= 3; ++person) {
        int p = inf.readInt(1, 100, "p_i");
        for (int i = 1; i <= p; ++i) {
            inf.readSpace();
            inf.readInt(1, n, "dish_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
