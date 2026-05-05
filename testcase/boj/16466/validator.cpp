#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of sold tickets in the first round
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the list of sold ticket numbers A_i
    // Each A_i must satisfy 1 ≤ A_i ≤ 2^31 − 1
    inf.readInts(N, 1, 2147483647, "A_i");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
