#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "N");
    inf.readEoln();

    for (int i = 1; i <= n + 1; ++i) {
        // CHECK: The statement omits explicit bounds for the erroneous number.
        // Treat every listed value as a friend count among N cows.
        inf.readInt(0, n - 1, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
