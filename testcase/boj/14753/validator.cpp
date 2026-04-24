#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate n
    int n = inf.readInt(3, 10000, "n");
    inf.readEoln();

    // Read and validate the n card values
    inf.readInts(n, -1000, 1000, "a_i");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
