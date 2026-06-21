#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 5000000, "M");
    inf.readEoln();
    int n = inf.readInt(1, 5000000, "N");
    inf.readEoln();
    ensuref(1LL * m * n <= 5000000LL, "M * N must be at most 5000000, got %lld",
            1LL * m * n);

    int k = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        std::string choice = inf.readToken("R|C", "choice");
        inf.readSpace();
        if (choice == "R") {
            inf.readInt(1, m, "row");
        } else {
            inf.readInt(1, n, "column");
        }
        inf.readEoln();
    }

    inf.readEof();
}
