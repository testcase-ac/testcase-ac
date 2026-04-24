#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read sequence A of length N
    inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
