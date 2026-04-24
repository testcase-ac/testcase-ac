#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(3, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N - 2, "K");
    inf.readEoln();

    // Read sequence V of length N
    inf.readLongs(N, -5000000LL, 5000000LL, "V");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
