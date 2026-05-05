#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 250000, "N");
    inf.readEoln();

    // Read Ci for each of the N rooms
    inf.readLongs(N, 0LL, 1000000000000LL, "C_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
