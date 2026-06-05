#include "testlib.h"

#include <vector>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    std::vector<int> a = inf.readInts(n, -1000000, 1000000, "a_i");
    inf.readEoln();

    inf.readEof();
}
