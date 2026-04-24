#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read the labels A_i
    // 0 ≤ A_i < 2^30
    long long MAXA = (1LL << 30) - 1;
    inf.readLongs(N, 0LL, MAXA, "A");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
