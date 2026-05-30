#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1'000'000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1'000'000, "K");
    inf.readEoln();
    (void)N;
    (void)K;
    inf.readEof();
}
