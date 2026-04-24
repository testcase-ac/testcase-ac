#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // Read B sequence
    // Each B_i must be between 1 and N+1 inclusive
    inf.readInts(N, 1, N + 1, "B_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
