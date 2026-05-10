#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the satisfaction values s_1 ... s_N
    // Each s_i must be between 1 and 1e9 inclusive
    inf.readLongs(N, 1LL, 1000000000LL, "s_i");
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
