#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int T = inf.readInt(1, 1000000000, "T");
    inf.readEoln();

    // Read array a of size N
    inf.readInts(N, 1, 1000000000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
