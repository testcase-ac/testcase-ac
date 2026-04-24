#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read the array of N non-negative integers up to 1e9
    inf.readLongs(N, 0LL, 1000000000LL, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
