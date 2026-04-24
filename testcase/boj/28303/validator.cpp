#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 500000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 2000, "K");
    inf.readEoln();

    // Read array a of length N
    inf.readLongs(N, 0LL, 1000000000LL, "a_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
