#include "testlib.h"

#include <vector>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    std::vector<long long> heights = inf.readLongs(n, 1LL, 1000000000LL, "H_i");
    inf.readEoln();

    inf.readEof();
}
