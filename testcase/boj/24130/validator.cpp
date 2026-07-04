#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int W = inf.readInt(1, 1000, "W");
    inf.readSpace();
    int H = inf.readInt(1, 1000, "H");
    inf.readEoln();

    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    std::string turns = inf.readToken("[LR]{1,10000}", "turns");
    ensuref(static_cast<int>(turns.size()) == N,
            "turn string length is %d, expected %d",
            static_cast<int>(turns.size()),
            N);
    inf.readEoln();

    inf.readEof();
    return 0;
}
