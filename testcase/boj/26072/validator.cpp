#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int l = inf.readInt(1, 100000, "L");
    inf.readEoln();

    inf.readInts(n, 0, l, "x_i");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "w_i");
    inf.readEoln();

    inf.readEof();
}
