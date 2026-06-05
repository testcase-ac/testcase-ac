#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 9, "K");
    inf.readEoln();

    // CHECK: The Korean statement says n <= 1000; the English legacy variant says n <= 10.
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 32000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
