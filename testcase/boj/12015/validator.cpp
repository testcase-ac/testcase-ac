#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the sequence
    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the sequence A of length N
    inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
