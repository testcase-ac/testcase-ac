#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read sequence A[1..N], each in range [-1e9, 1e9]
    inf.readLongs(N, -1000000000LL, 1000000000LL, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
