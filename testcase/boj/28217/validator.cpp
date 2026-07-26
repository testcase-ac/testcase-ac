#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    for (int triangle = 0; triangle < 2; ++triangle) {
        for (int row = 1; row <= n; ++row) {
            inf.readInts(row, 0, 1, triangle == 0 ? "a_i_j" : "b_i_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
