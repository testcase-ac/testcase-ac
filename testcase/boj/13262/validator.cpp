#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read array A of size N, each between 0 and 2^30
    const long long MAX_A = (1LL << 30);
    inf.readLongs(N, 0LL, MAX_A, "A_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
