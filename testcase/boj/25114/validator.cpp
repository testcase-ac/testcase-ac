#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    inf.readInts(n, 0, (1 << 30) - 1, "a_i");
    inf.readEoln();

    inf.readInts(n, 0, (1 << 30) - 1, "b_i");
    inf.readEoln();

    inf.readEof();
}
