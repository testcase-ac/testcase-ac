#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean BOJ statement says T < 10, while the English variant
    // says K < 1000. This validator follows the primary BOJ statement.
    int t = inf.readInt(1, 9, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 20000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
