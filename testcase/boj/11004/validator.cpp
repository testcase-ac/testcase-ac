#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N and K
    int N = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read and validate the array A of size N
    // Each A_i must be in range [-1e9, 1e9]
    inf.readInts(N, -1000000000, 1000000000, "A_i");
    inf.readEoln();

    // No more input allowed
    inf.readEof();
    return 0;
}
