#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    // CHECK: The written limit says K <= N, but official samples use K > N.
    // Interpret the bound as 1 <= K <= 5,000,000, consistent with N and M.
    inf.readInt(1, 5000000, "K");
    inf.readSpace();
    inf.readInt(1, n, "M");
    inf.readEoln();
    inf.readEof();
}
