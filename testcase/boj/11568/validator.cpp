#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the sequence of N integers
    inf.readInts(N, 1, 100000000, "a");
    inf.readEoln();

    inf.readEof();
    return 0;
}
