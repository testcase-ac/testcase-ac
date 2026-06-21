#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2000, "M");
    inf.readEoln();

    inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    inf.readInts(M, 1, 1000, "B_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
